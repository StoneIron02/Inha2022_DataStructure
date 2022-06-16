/*
* C++ �̿��Ͽ� AVL Tree �����ϱ�
*
* ���� : AVL Tree ���� �ϱ� ���� �ۼ�������,
*       C++ �̿��Ͽ� �ۼ��Ͻô� �е鿡�� ������ �ǰ��� �ߴ�.
*
* ���� : key ���� int�� ���� �ϸ� �ߺ� key�� ��� x
*       �ܼ� ���� ����Ʈ�� ����
*
*       class AVLTree
*
*       ���� :   root => root node
*
*       ������ : RBTREE =>  root �� null�� �ʱ�ȭ
*
*       �Լ� :   IsKey => key���� �ִ��� �˻��ϴ� �Լ�
*
*               Insert => ��͸� �̿��� ���� �Լ� (���������� root�� return)
*               Delete => ��͸� �̿��� ���� �Լ� (�������� root�� return)
*               Balancing => ���� / ������ BF �˻��Ͽ� ��Ģ�������� ������ �Լ�
*               Transplant => ���� �� �̿��ϸ�, ������ ����� �ڽ� ��带 �θ��忡 �������ִ� �Լ�
*
*               getHeight(x) => x�� ���� getter
*               getBalanceBacotr(x) => x�� BF ����Ͽ� return
*               RotateRight(x) => x���� ���������� ȸ��
*               RotateLeft(x) => x���� �������� ȸ��
*
*               Inorder,Preorder,Postorder => ��ȸ �Լ�
*               tree_minimum(x), tree_maximum(x) => ��� x �������� ���� ����, ������ return �Լ�
*
*               DisplayMenu, SelectMenu => �ʱ� Menu�� print �Լ�
*               Insert_helper,Delete_helper,order_helper,print_helper => ���� �̺�Ʈ ����� �Է¹ް� ���� ���� ó�� ���� �Լ� �� tree print ���ִ� �Լ�
*
*        Balancing���� �� case�� ���� ������ github�� ���� ���Ҵ�.
*
* �ۼ��� : gowoonsori
* github : https://github.com/gowoonsori/my-tech/tree/master/dataStructure/Tree
*/

#include <algorithm>  // max() �Լ� �̿�
#include <iostream>

struct node {
    int key;
    node* left = nullptr;
    node* right = nullptr;
    int height = 1;
};
typedef node* NodePtr;

class AVLTREE {
private:
    NodePtr root;  //��Ʈ ���

    //key���� �ִ��� ������ �˻� ������ pointer ��, ������ nullptr
    NodePtr IsKey(int item) {
        NodePtr t = root;

        /*key���� ã�ų� ���ٸ� break*/
        while (t != nullptr && t->key != item) {
            t = (item < t->key) ? t->left : t->right;
        }
        return t;
    }

    /*���ο� key �����Լ��� root��� ��ȯ*/
    NodePtr Insert(NodePtr r, int item) {
        /*���ο� ��� ����*/
        if (r == nullptr) {
            NodePtr z = new node;
            z->key = item;
            r = z;
            return r;
        }
        else if (r->key < item) {  //item�� key������ ũ�ٸ� ���������� �̵�
            r->right = Insert(r->right, item);
        }
        else {  //item�� key������ �۴ٸ� �������� �̵�
            r->left = Insert(r->left, item);
        }
        r->height = std::max(getHeight(r->left), getHeight(r->right)) + 1;
        Balancing(r, item);  //���ο� ��尡 �߰��Ǿ����Ƿ� ��������� �θ���� ���� 1���� �����ְ�
                             //Balace Factor �����Ͽ� 2�̻��̶�� �������Լ�
        return r;
    }

    /*key ���� �Լ�*/
    NodePtr Delete(NodePtr r, int item) {
        if (r->key > item && r->left != nullptr) {
            r->left = Delete(r->left, item);
        }
        else if (r->key < item && r->right != nullptr) {
            r->right = Delete(r->right, item);
        }
        else if (r->key == item) {
            Transplant(r);
        }
        /*root�� ����� �ƴ϶��*/
        if (r != nullptr) {
            r->height = std::max(getHeight(r->left), getHeight(r->right)) + 1;
            Balancing(r, item);
        }

        return r;
    }

    /* balance Factor ������ ������*/
    void Balancing(NodePtr& r, int item) {
        int bF = getBalanceFactor(r);

        //case 1 (left left)
        if (bF > 1 && item < r->left->key) {
            r = RotateRight(r);
        }
        //case 2 (left right)
        else if (bF > 1 && item > r->left->key) {
            r->left = RotateLeft(r->left);
            r = RotateRight(r);
        }
        //case 3 (right right)
        else if (bF < -1 && item > r->right->key) {
            r = RotateLeft(r);
        }
        //case 4 ( right left)
        else if (bF < -1 && item < r->right->key) {
            r->right = RotateRight(r->right);
            r = RotateLeft(r);
        }
    }

    /* ������ �ڽ� �̽� �Լ�*/
    void Transplant(NodePtr& x) {
        NodePtr y = x;  //y�� ���� ��� ����

        if (x->left == nullptr) {
            x = x->right;
        }
        else if (x->right == nullptr) {
            x = x->left;
        }
        else {
            NodePtr z = x->right;  //z : ������ x�� �������� ���� ���� ��
            NodePtr pZ = x;        //p[z] : z�� �θ� ���

            /* ������ �ڽ��� ���� ���� ��*/
            while (z->left != nullptr) {
                pZ = z;
                z = z->left;
            }

            x->key = z->key;  //successor�� key�� ��ȯ

            /*������ �ڽ��� ���� �۴ٸ�*/
            if (pZ == x) {
                x->right = z->right;  // z�� ������ �ڽ� �ٿ��ֱ�
            }
            else {
                pZ->left = z->right;  // ������ �ڽ��� ���� �ڽ��� �ִٸ�
            }                         // �� z(successor)�� ������ �ڽ� p[z]�� ���ʿ� �ٿ��ֱ�
            y = z;                    //�� ������ ���� y <- z;
        }
        delete y;
    }
    /*���� getter */
    int getHeight(NodePtr r) {
        if (r == nullptr)
            return 0;
        else
            return r->height;
    }
    /*�¿� �ڽ� ���� ���Ͽ� Balnace Factor get*/
    int getBalanceFactor(NodePtr r) {
        return getHeight(r->left) - getHeight(r->right);
    }

    /*x�� �߽����� �������� ȸ��*/
    NodePtr RotateLeft(NodePtr x) {
        NodePtr y = x->right;
        x->right = y->left;
        y->left = x;

        //��ġ�� �ٲ�����Ƿ� ���� ������
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }
    /*y�� �߽����� ���������� ȸ��*/
    NodePtr RotateRight(NodePtr y) {
        NodePtr x = y->left;
        y->left = x->right;
        x->right = y;

        //��ġ�� �ٲ�����Ƿ� ���� ������
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    /*show tree*/
    void print_helper(NodePtr root, std::string indent, bool last) {
        // print the tree structure on the screen
        if (root != nullptr) {
            std::cout << indent;
            if (last) {
                std::cout << "R----";
                indent += "     ";
            }
            else {
                std::cout << "L----";
                indent += "|    ";
            }

            int height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
            std::cout << root->key << " (" << height << ")" << std::endl;
            print_helper(root->left, indent, false);
            print_helper(root->right, indent, true);
        }
    }

    /*������ȸ*/
    void Inorder(NodePtr target) {
        if (target == nullptr)
            return;
        Inorder(target->left);
        std::cout << target->key << " ";
        Inorder(target->right);
    }
    /*������ȸ*/
    void Postorder(NodePtr target) {
        if (target == nullptr)
            return;
        Postorder(target->left);
        Postorder(target->right);
        std::cout << target->key << " ";
    }
    /*������ȸ*/
    void Preorder(NodePtr target) {
        if (target == nullptr)
            return;
        std::cout << target->key << " ";
        Preorder(target->left);
        Preorder(target->right);
    }

public:
    AVLTREE() {
        this->root = nullptr;
    }
    //�ּڰ� ã��
    NodePtr tree_minimum(NodePtr x) {
        while (x->left != nullptr) {
            x = x->left;
        }
        return x;
    }
    //�ִ� ã��
    NodePtr tree_maximum(NodePtr x) {
        while (x->right != nullptr) {
            x = x->right;
        }
        return x;
    }

    void DisplayMenuBoard() {
        std::cout << "         ** AVL Tree **     " << std::endl;
        std::cout << "                            " << std::endl;
        std::cout << "              Menu          " << std::endl;
        std::cout << "          1. Insert Key     " << std::endl;
        std::cout << "          2. Delete Key     " << std::endl;
        std::cout << "          3. Show Tree      " << std::endl;
        std::cout << "          4. choose order   " << std::endl;
        std::cout << "          5. show Menu      " << std::endl;
        std::cout << "          6. clear Display  " << std::endl;
        std::cout << "          7. exit           " << std::endl;
        std::cout << std::endl;
    }
    void SelectMenu() {
        DisplayMenuBoard();
        int i = -1;

        while (i != 8) {
            std::cout << "(show Menu : 5) -->  select :   ";
            std::cin >> i;
            switch (i) {
            case 1:
                Insert_helper();
                break;
            case 2:
                Delete_helper();
                break;
            case 3:
                print_helper(root, "", true);
                break;
            case 4:
                Order_helper();
                break;
            case 5:
                DisplayMenuBoard();
                break;
            case 6:
                system("cls");
                DisplayMenuBoard();
                break;
            case 7:
                return;
            default:
                std::cout << " !!! Wrong entered !!!\n"
                    << std::endl;
            }
        }
    }

    void Insert_helper() {
        int item;
        std::cout << "Key to insert  :  ";
        std::cin >> item;
        if (IsKey(item)) {
            std::cout << "!!! " << item << " is already exists !!!\n";
            return;
        }
        this->root = Insert(this->root, item);
        return;
    }

    void Delete_helper() {
        int item;
        std::cout << "Key to delete  :  ";
        std::cin >> item;
        if (!IsKey(item)) {
            std::cout << "!!! " << item << " is not exists !!!\n";
            return;
        }
        this->root = Delete(this->root, item);
        return;
    }

    void Order_helper() {
        int i;
        std::cout << "         == Order Menu ==" << std::endl;
        std::cout << "          1. PreOrder" << std::endl;
        std::cout << "          2. InOrder" << std::endl;
        std::cout << "          3. PostOrder" << std::endl;
        std::cout << "          4. exit" << std::endl;
        std::cout << " --> select  :  ";

        std::cin >> i;
        switch (i) {
        case 1:
            Preorder(this->root);
            std::cout << std::endl;
            break;
        case 2:
            Inorder(this->root);
            std::cout << std::endl;
            break;
        case 3:
            Postorder(this->root);
            std::cout << std::endl;
            break;
        case 4:
            return;
        default:
            std::cout << " !!! Wrong enter !!!\n"
                << std::endl;
            break;
        }
        return;
    }
};

int main() {
    AVLTREE tree;
    tree.SelectMenu();

    return 0;
}