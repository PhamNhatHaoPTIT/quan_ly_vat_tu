#include "iostream"

using namespace std;

struct material {
    string materialId, materialName, unit;
    int numberInStock;
};
typedef struct material MATERIAL;

struct MaterialNodeTree {
    MATERIAL material;
    MaterialNodeTree *left;
    MaterialNodeTree *right;
    int height;
};
typedef struct MaterialNodeTree *MATERIAL_NODE_TREE;

MATERIAL_NODE_TREE NewNode(MATERIAL material) {
    MATERIAL_NODE_TREE node = new MaterialNodeTree;
    node->material = material;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int getMaterialNodeTreeHeight(MATERIAL_NODE_TREE root) {
    if (root == NULL) return 0;
    return root->height;
}

int getBalance(MATERIAL_NODE_TREE root) {
    if (root == NULL) return 0;
    return getMaterialNodeTreeHeight(root->left) - getMaterialNodeTreeHeight(root->right);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

MATERIAL_NODE_TREE rightRotate(MATERIAL_NODE_TREE y) {
    MATERIAL_NODE_TREE x = y->left;
    MATERIAL_NODE_TREE T2 = x->right;
    x->right = y;
    y->left = T2;
    // cap nhat chieu cao cay
    y->height = max(getMaterialNodeTreeHeight(y->left), getMaterialNodeTreeHeight(y->right)) + 1;
    x->height = max(getMaterialNodeTreeHeight(x->left), getMaterialNodeTreeHeight(x->right)) + 1;
    return x;
}

MATERIAL_NODE_TREE leftRotate(MATERIAL_NODE_TREE x) {
    MATERIAL_NODE_TREE y = x->right;
    MATERIAL_NODE_TREE T2 = y->left;
    y->left = x;
    x->right = T2;
    // cap nhat chieu cao cay
    x->height = max(getMaterialNodeTreeHeight(x->left), getMaterialNodeTreeHeight(x->right)) + 1;
    y->height = max(getMaterialNodeTreeHeight(y->left), getMaterialNodeTreeHeight(y->right)) + 1;
    return y;
}

MATERIAL_NODE_TREE addMaterialTree(MATERIAL_NODE_TREE &node, MATERIAL material) {
    if (node == NULL) return (NewNode(material));

    if (material.materialId < node->material.materialId)
        node->left = addMaterialTree(node->left, material);
    else if (material.materialId > node->material.materialId)
        node->right = addMaterialTree(node->right, material);
    else return node;

    node->height = 1 + max(getMaterialNodeTreeHeight(node->left), getMaterialNodeTreeHeight(node->right));

    int balance = getBalance(node);
    // mat can bang trai-trai
    if (balance > 1 && material.materialId < node->left->material.materialId)
        return rightRotate(node);
    // mat can bang phai-phai
    if (balance < -1 && material.materialId > node->right->material.materialId)
        return leftRotate(node);
    // mat can bang trai-phai
    if (balance > 1 && material.materialId > node->left->material.materialId) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // mat can bang phai-trai
    if (balance < -1 && material.materialId < node->right->material.materialId) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

MATERIAL_NODE_TREE findMinValueNode(MATERIAL_NODE_TREE node) {
    MATERIAL_NODE_TREE current = node;

    while (current->left != NULL)
        current = current->left;
    return current;
}

MATERIAL_NODE_TREE deleteMaterialById(MATERIAL_NODE_TREE &root, string materialId) {
    if (root == NULL)
        return root;

    if (materialId < root->material.materialId)
        root->left = deleteMaterialById(root->left, materialId);
    else if (materialId > root->material.materialId)
        root->right = deleteMaterialById(root->right, materialId);
    else {
        if ((root->left == NULL) || (root->right == NULL))   // No child and one child case
        {
            MATERIAL_NODE_TREE temp = root->left ? root->left : root->right;
            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // One child case
                *root = *temp; // Copy the contents of
            // the non-empty child
            delete temp;
        } else // Two child case
        {
            MATERIAL_NODE_TREE temp = findMinValueNode(root->right);
            // Copy the inorder successor's data to this node
            root->material = temp->material;
            // Delete the inorder successor
            root->right = deleteMaterialById(root->right, temp->material.materialId);
        }
    }
    // If the tree had only one node then return
    if (root == NULL) return root;

    root->height = 1 + max(getMaterialNodeTreeHeight(root->left), getMaterialNodeTreeHeight(root->right));
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void preOrder(MATERIAL_NODE_TREE root) {
    if (root != NULL) {
        cout << "Vat tu: " << root->material.materialId << "\n";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void deleteTree(MATERIAL_NODE_TREE &root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

MATERIAL inputMaterial() {
    MATERIAL result;
    cout << "\nNhap ma vat tu: ";
    cin >> result.materialId;
    cout << "\nNhap ten vat tu: ";
    cin >> result.materialName;
    cout << "\nNhap so luong ton ";
    cin >> result.numberInStock;
    cout << "\nNhap don vi tinh: ";
    cin >> result.unit;
    cout << "\n";
    return result;
}

void printMaterial(MATERIAL material) {
    cout << "Ten vat tu: " << material.materialName;
    cout << "\nMa vat tu: " << material.materialId;
}