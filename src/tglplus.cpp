#include <iostream>

#define PRINT_UARCH_NAME 1
#define AVX10_ISA_BIT 0x00080000


struct CpuidResult
{
    uint32_t EAX;
    uint32_t EBX;
    uint32_t ECX;
    uint32_t EDX;
};

// detect CPU model using CPUID instruction
uint32_t detectIntelCPUModel()
{
    uint32_t leaf, subleaf;
    CpuidResult cpuInfo;
    leaf = 0x01;
    subleaf = 0x00;
    __cpuidex((int *)&cpuInfo, leaf, subleaf);

    uint32_t family = ((cpuInfo.EAX >> 8) & 0xF);
    uint32_t model = ((cpuInfo.EAX >> 4) & 0xF);
    uint32_t extFamily = ((cpuInfo.EAX >> 20) & 0xFF);
    uint32_t extModel = ((cpuInfo.EAX >> 16) & 0xF);

    if (family == 6)
    {
        model += (extModel << 4); // Extended model
    }
    return model;
}

// detect AVX10 support using CPUID instruction
bool hasAVX10Support()
{
    uint32_t leaf, subleaf, avx10IsaSet;
    CpuidResult cpuInfo;
    bool AVX10Support = false;

    // Check OSXSAVE for AVX support
    // if cpu supports extended features
    cpuInfo = {0, 0, 0, 0};
    leaf = 0x00;
    subleaf = 0x00;
    __cpuidex((int *) &cpuInfo, leaf, subleaf);
    if (cpuInfo.EAX < 7) {
        return false; // CPU does not support extended features leaf
    }

    cpuInfo = {0, 0, 0, 0};
    leaf = 0x01;
    subleaf = 0x00;
    __cpuidex((int *) &cpuInfo, leaf, subleaf);
    if (!(cpuInfo.ECX & (1 << 27))) { // Bit 27 of ECX is OSXSAVE
        return false; // OS does not support AVX state management
    }

    // Check AVX and AVX512 feature bits
    if (!(cpuInfo.ECX & (1 << 28))) { // Bit 28 of ECX is AVX
        return false;
    }

    // Check AVX10 support in leaf 7 subleaf 1
    cpuInfo = {0, 0, 1, 0};
    leaf = 0x07;
    subleaf = 0x01;
    __cpuidex((int *) &cpuInfo, leaf, subleaf);
    AVX10Support = cpuInfo.EDX & AVX10_ISA_BIT;

    return AVX10Support;
}

// detect if CPU model is Tiger Lake or greater (table)
bool tigerLakePlusDetect()
{
    bool tigerLakePlus;
    std::string modelName;
    uint32_t model = detectIntelCPUModel();

#ifdef PRINT_UARCH_NAME
    // print model name for debugging
    switch (model)
    {
    case 0x8C: // Tiger Lake
    case 0x8D: // Tiger Lake Refresh
        modelName = " Tiger Lake ";
        break;
    case 0x8F: // Sapphire Rapids (Golden Cove)
    case 0x97: // Alder Lake S (Golden Cove)
    case 0x9A: // Alder Lake (Golden Cove)
    case 0x9D: // Alder Lake P (Golden Cove)
    case 0xB7: // Raptor Lake (Golden Cove)
    case 0xBA: // Raptor Lake S (Golden Cove)
    case 0xBF: // Raptor Lake HX (Golden Cove)
        modelName = " Golden Cove ";
        break;
    case 0xAA: // Meteor Lake P/M (Redwood Cove)
    case 0xAC: // Meteor Lake S (Redwood Cove)
    case 0xAD: // Granite Rapids (Redwood Cove)
    case 0xAE: // Meteor Lake U/Y (Redwood Cove)
    case 0xB5: // Arrow Lake U
    case 0xC5: // Arrow Lake P
    case 0xC6: // Arrow Lake S/HX
        modelName = " Redwood Cove ";
        break;
    case 0xBD: // Lunar Lake, (Lion Cove)
        modelName = " Lion Cove ";
        break;
    case 0xCC: // Panther Lake
        modelName = " Panther Cove ";
        break;
    default:
        modelName = " Unknown ";
        break;
    }
    std::cout << "Model detected: " << modelName << "(0x" << std::hex << model << ")" << std::endl;
#endif

    switch (model)
    {
    case 0x8C: // Tiger Lake
    case 0x8D: // Tiger Lake Refresh
    case 0x8F: // Sapphire Rapids (Golden Cove)
    case 0x97: // Alder Lake S (Golden Cove)
    case 0x9A: // Alder Lake (Golden Cove)
    case 0x9D: // Alder Lake P (Golden Cove)
    case 0xB7: // Raptor Lake (Golden Cove)
    case 0xBA: // Raptor Lake S (Golden Cove)
    case 0xBF: // Raptor Lake HX (Golden Cove)
    case 0xAA: // Meteor Lake P/M (Redwood Cove)
    case 0xAC: // Meteor Lake S (Redwood Cove)
    case 0xAD: // Granite Rapids (Redwood Cove)
    case 0xAE: // Meteor Lake U/Y (Redwood Cove)
    case 0xB5: // Arrow Lake U
    case 0xC5: // Arrow Lake P
    case 0xC6: // Arrow Lake S/HX
    case 0xBD: // Lunar Lake, (Lion Cove)
    case 0xCC: // Panther Lake
        tigerLakePlus = true;
        break;
    default:
        tigerLakePlus = false;
        break;
    }
    return tigerLakePlus;
}

// main function test application
int main(int argc, char *argv[])
{
    std::string modelDetect = "";
    std::string AVX10Detect = "";

    std::cout << "Detect Intel Tiger Lake Plus" << std::endl;

    // detect CPU model and AVX10 support
    bool modelGreater = tigerLakePlusDetect();
    bool hasAVX10 = hasAVX10Support();

    if (modelGreater)
    {
        modelDetect = "Model detected to be >= Tiger Lake.";
    }
    else
    {
        modelDetect = "Model not in list.";
    }
    if (hasAVX10 == true)
    {
        AVX10Detect = "AVX 10 supported.";
    }
    else
    {
        AVX10Detect = "AVX 10 not supported.";
    }

    std::cout << modelDetect << std::endl;
    std::cout << AVX10Detect << std::endl;

    return 0;
}
