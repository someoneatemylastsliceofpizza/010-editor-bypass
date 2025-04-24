#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage: %s path/to/010Editor.exe or Drag and drop", argv[0]);
        system("pause");
        return 1;
    }
    std::fstream file(argv[1], std::ios::in | std::ios::out | std::ios::binary);
    if (!file) {
        printf("Failed to open file. Try run as admin.\n");
        system("pause");
        return 1;
    }
    file.seekp(0x1F481F);
    unsigned char original[] = { 0xBA,0x0D,0x00,0x00,0x00,0x41,0xB8,0xC7,
                                 0x49,0x00,0x00,0x48,0x8B,0x0D,0x1F,0x9A,
                                 0xB0,0x00,0xE8,0xE2,0x0C,0xE1,0xFF };
    unsigned char check[0x17];
    file.read(reinterpret_cast<char*>(check), sizeof(check));
    bool isSame = std::equal(std::begin(original), std::end(original), std::begin(check));
    if (!isSame) {
        printf("Failed File version not match or Alredy patched.\n");
        system("pause");
        return 1;
    }

    file.seekp(0x1F481F);
    unsigned char patch1[] = { 0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,
                                0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,
                                0x90,0x90,0xB8,0x93,0x00,0x00,0x00 };

    file.write(reinterpret_cast<char*>(patch1), sizeof(patch1));

    file.seekp(0x1F487A);
    unsigned char patch2[] = { 0xE9,0xCB,0x00 };
    file.write(reinterpret_cast<char*>(patch2), sizeof(patch2));

    file.seekp(0x1F487F);
    unsigned char patch3[] = { 0x90 };
    file.write(reinterpret_cast<char*>(patch3), sizeof(patch3));

    file.seekp(0x1F494A);
    unsigned char patch4[] = { 0xEB };
    file.write(reinterpret_cast<char*>(patch4), sizeof(patch4));

    file.seekp(0x1F4975);
    unsigned char patch5[] = { 0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,
                               0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,
                               0x90,0x90,0xB8,0xDB,0x00,0x00,0x00 };
    file.write(reinterpret_cast<char*>(patch5), sizeof(patch5));

    file.close();
    printf("Done!\n");
    system("pause");

    return 0;
}
