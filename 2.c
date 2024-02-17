#include <malloc.h>
struct s_tree_node{
    struct s_tree_node *right;
    struct s_tree_node *left;
    int data;
};
typedef struct s_tree_node node;
void insert(node ** tree, int val);
void tree_mem_free(node ** tree);
int main(){
    return 0;
}

void tree_mem_free(node ** tree){
    if(*tree){
        if((*tree)->left) {
            tree_mem_free(&(*tree)->left);
        }
        if((*tree)->right) {
            tree_mem_free(&(*tree)->right);
        }
        if(!( (*tree)->right || (*tree)->left) ){
            free(*tree);
            (*tree) = NULL;
        }
    }
}


void insert(node ** tree, int val)
{
    node *temp = NULL;
    if(!(*tree)) {//если указывает не в занятое
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;temp->data = val;
        *tree = temp;
        return;
    }
    if(val < (*tree)->data) {//если уже занято но значение меньше
        insert(&(*tree)->left, val);
    } else if(val > (*tree)->data) {
        insert(&(*tree)->right, val);
    }
}
