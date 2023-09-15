#include "iostream"
#include "Material.cpp"

using namespace std;

int main() {
    MATERIAL_NODE_TREE root = NULL;
    cout << "Chuong trinh quan ly vat tu\n";
    int userChoose;
    do {
        cout << "Cac chuc nang cua chuong trinh la\n";
        cout << "1. Them vat tu\n";
        cout << "2. Sua vat tu\n";
        cout << "3. Xoa vat tu\n";
        cout << "Ban hay nhap lua chon cua minh: ";
        cin >> userChoose;
        switch (userChoose) {
            case 1:
                MATERIAL material = inputMaterial();
                root = addMaterialTree(root, material);
                preOrder(root);
                break;
        }
    } while (userChoose > 0);
    deleteTree(root);
    return 0;
}
