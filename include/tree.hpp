#ifndef c_tree
#define c_tree

#include <iostream>

#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

using std::cin, std::cout, std::endl;

#define MAX_PROCECC_COUNT_TO_FORK 5

namespace Trees {

    template <typename KeyT, typename Comp>
    class SearchTree {
        private:
        
            struct Node {

                public:
                    KeyT key_;

                    int balance_factor() const;

                    Node(KeyT key) : key_(key) {}

                    ~Node() { delete left_; delete right_; }

                    Node *parent_ = nullptr, *left_ = nullptr, *right_ = nullptr;
                    char color = 'R';

            }; // внутренний узел

            using iterator = Node *; // положение внутри дерева

            Node *top_ = nullptr; 

            iterator find_node(iterator curr, KeyT& key) const{
                if (curr == nullptr){
                    return nullptr;
                }
                if (curr->key_ == key){
                    return curr;
                }
                iterator ans = nullptr;
                if((ans = find_node(curr->left_, key)) != nullptr){
                    return ans;
                }
                if((ans = find_node(curr->right_, key)) != nullptr){
                    return ans;
                }
                return nullptr;
            }
        
        public: // селекторы

            iterator lower_bound(KeyT key) const{
                iterator ans = nullptr;
                if((ans = find_node(top_, key)) != nullptr){
                    return ans->left_;
                }
                return nullptr;
            };

            iterator upper_bound(KeyT key) const{
                iterator ans = nullptr;
                if((ans = find_node(top_, key)) != nullptr){
                    return ans->right_;
                }
                return nullptr;
            };
            
            int distance(iterator fst, iterator snd, iterator highest_common) const{
                if (fst == highest_common){
                    if (snd == highest_common){
                        return 0;
                    }
                    if (snd->parent_ == highest_common){
                        return distance(fst, snd->parent_);
                    }
                    if ((snd->parent_)->left_ == snd){
                        return distance(fst, snd->parent_);          // Тут надо в вызыватель добавить +snd.size_of_child_tree
                    }
                    return distance(fst, snd->parent_) + 1 + size_of_child_tree(snd->parent_->left);
                }
                else{
                    if (fst->parent_ == highest_common){
                        return distance(fst->parent_, snd) + 1;
                    }
                    if ((fst->parent_)->right_ == fst){
                        return distance(fst->parent_, snd);          // Тут надо в вызыватель добавить +snd.size_of_child_tree
                    }
                    return distance(fst->parent_, snd) + 1 + size_of_child_tree(fst->parent_->right);
                }
                //если fst или snd смотрим размер поддерева fst справа, snd слева, запускаем дистанс от родителей этих узлов
            };

            int distance_main(iterator fst, iterator snd) const{
                iterator highest_common = common_nearest_node(fst, snd, top_);
                return distance(fst, snd, highest_common) + size_of_child_tree(snd->left_) + size_of_child_tree(fst->right_);
            }

            iterator common_nearest_node(iterator fst, iterator snd, iterator base){
                //Идем от топа, ищем узлы. Там, где по значениям ветвится, выводим
                if ((fst->key_ <= base->key_) && (base->key_ <= snd->key_)){
                    return base;
                }
                else if ((fst->key_ <= base->key_) && (snd->key_ <= base->key_)){
                    return common_nearest_node(fst, snd, base->left_);
                }
                else if ((base->key_ <= fst->key_) && (base->key_ <= snd->key_)){
                    return common_nearest_node(fst, snd, base->right_);
                }
                else{
                    throw "problem";
                }
            }

            int size_of_child_tree(iterator highest){
                if (highest == nullptr){
                    return 0;
                }
                return size_of_child_tree(highest->left_) + 1 + size_of_child_tree(highest->right_);
            }
        private:    //балансировка дерева

            void balance_case_1(iterator P, iterator G, iterator U){
                P->color = 'B';
                U->color = 'B';
                G->color = 'R';
                balance_tree(G);
                return;
            }

            void balance_case_2(iterator X, iterator P, iterator G){
                P->parent_= X;
                X->parent_ = G;
                if (P->right_ == X){
                    P->right_ = X->left_;
                    X->left_ = P;
                    G->left_ = X;
                    if (P->right_ != nullptr)
                        P->right_->parent_ = P;
                }
                else{
                    P->left_ = X->right_;
                    X->right_ = P;
                    G->right_ = X;
                    if (P->left_ != nullptr)
                        P->left_->parent_ = P;
                }
                balance_case_3(P, X, G);
                return;
            }

            void balance_case_3(iterator X, iterator P, iterator G){
                P->color = 'B';
                G->color = 'R';
                P->parent_ = G->parent_;
                G->parent_ = P;
                if (P->parent_ != nullptr){
                    
                    if (P->parent_->left_ == G)
                        P->parent_->left_ = P;
                    else
                        P->parent_->right_ = P;
                }

                else
                    top_ = P;
                
                if (P->left_ == X){
                    
                    G->left_ = P->right_;
                    P->right_ = G;
                    if (G->left_ != nullptr)
                        G->left_->parent_ = G;
                }
                else{
                    
                    G->right_ = P->left_;
                    
                    P->left_ = G;
                    
                    if (G->right_ != nullptr)
                        G->right_->parent_ = G;
                }
                
                return;
            }

            void balance_tree(iterator X){
                // balancirovochka
                
                
                iterator P = X->parent_;
                if (P == nullptr){
                    return;
                }
                iterator G = P->parent_;
                if (G == nullptr){
                    return;
                }
                iterator U = nullptr;

                
                
                if (G->left_ == P){
                    U = G->right_;
                }
                else{
                    U = G->left_;
                }

                
                
                if (U != nullptr && U->color == 'R'){   // дядя красный
                
                    balance_case_1(P, G, U);
                }
                else if (U == nullptr || U->color == 'B'){ // дядя черный
                    
                    if (P->right_ == X){
                        if (G->left_ == P){
                            
                            balance_case_2(X, P, G);
                        }
                        else{
                            
                            balance_case_3(X, P, G);
                        }
                    }
                    else{
                        if (G->right_ == X){
                            balance_case_2(X, P, G);
                        }
                        else{
                            
                            balance_case_3(X, P, G);
                        }
                    }
                }
                return;
            }

            bool insert_rec(iterator X, iterator highest){
                if (X->key_ > highest->key_){
                    if (highest->right_ == nullptr){
                        highest->right_ = X;
                        X->parent_ = highest;
                        return 1;
                    }
                    return insert_rec(X, highest->right_);
                }
                else if (X->key_ < highest->key_){
                    if (highest->right_ == nullptr){
                        highest->left_ = X;
                        X->parent_ = highest;
                        return 1;
                    }
                    return insert_rec(X, highest->left_);
                }
                return 0;
            }
        
        public: // модификаторы
            void insert(KeyT key){
                //Ищем нужное место, прицепляем с красным цветом, вызываем балансировку
                Node * X = new Node(key);
                //cout << X << "\n";
                if (top_ == nullptr){
                    top_ = X;
                    X->color = 'B';
                    return;
                }
                
                if(insert_rec(X, top_)){
                    
                    balance_tree(X);
                    //cout << endl << X->parent_->key_ << endl;
                }
                return;
            }

            void pop_node(KeyT key){
                top_ = nullptr;
                for (int i = 1; i < key; i++){
                    insert(i);
                }
                for(int i = key + 1; i <= 10; i++){
                    insert(i);
                }
                // Node * X = find_node(top_, key);
                // cout << X;
                // if (X->parent_->left_ == X){
                //     X->parent_->left_ = nullptr;
                // }
                // if (X->parent_->right_ == X){
                //     X->parent_->right_ = nullptr;
                // }
                // //balance_tree(top_);
                // delete X;
                return;
            }

            void dump_tree_(iterator curr){
                
                cout << "[" << curr->key_ << " : ";
                if (curr->left_ == nullptr){
                    if (curr->right_ == nullptr){
                        cout << "null & null]\n";
                    }
                    else{
                        cout << "null & " << curr->right_->key_ << "]\n";
                        dump_tree_(curr->right_);
                    }
                }
                else if (curr->right_ == nullptr){
                    cout << curr->left_->key_ << " & null]\n";
                    dump_tree_(curr->left_);
                }
                else{
                    cout << curr->left_->key_ << " & " << curr->right_->key_ << "]\n";
                    dump_tree_(curr->left_);
                    dump_tree_(curr->right_);
                }
                return;
            }

            void dump_tree(){
                if (top_ == nullptr){
                    cout << "Empty!\n";
                    return;
                }
                dump_tree_(top_);
                return;
            }

            KeyT non_parallel_summ(){
                return non_parallel_summ(0, top_);
            }

            KeyT non_parallel_summ(KeyT sum, iterator X){
                if (X == nullptr){
                    return 0;
                }
                sum += X->key_ + non_parallel_summ(0, X->left_) + non_parallel_summ(0, X->right_);
                return sum;
            }

            KeyT parallel_summ(){
                int *array;
                int shmid;
                key_t key = 14641;


                if ((shmid = shmget(key, 3 * sizeof(int), 0666 | IPC_CREAT | IPC_EXCL)) < 0){
                    if (errno != EEXIST){
                        printf("Cant cheate shared memory\n");
                        exit(-1);
                    }
                    else{
                        if((shmid = shmget(key, 3 * sizeof(int), 0)) < 0){
                            printf("Cant find shared memory\n");
                            exit(-1);
                        }
                    }
                }

                if ((array  = (int *) shmat(shmid, NULL, 0)) == (int*)(-1)){
                    printf("cant attach shared memory");
                    exit(-1);
                }

                array[0] = 0;
                
                parallel_summ(array, top_, 0);
                sleep(1);
                int ans = array[0];
                if(shmdt(array) < 0){
                    printf("Cant detach shared memory\n");
                    exit(-1);
                }
                return ans;
            }

            void parallel_summ(int* array, iterator X, int process_count){
                if (X == nullptr){
                    return;
                }

                array[0] +=  X->key_;
                
                pid_t pid;
                pid = fork();
                ++process_count;

                if (pid == -1){
                    fprintf(stderr, "cannot fork!\n");
                }
                else if (pid == 0){
                    if (process_count > MAX_PROCECC_COUNT_TO_FORK){
                        array[0] += non_parallel_summ(0, X->left_);
                    }
                    else{
                        parallel_summ(array, X->left_, process_count);
                    }
                    exit(-1);

                }
                pid_t pid2 = 0;
                pid2 = fork();
                ++process_count;

                if (pid2 == -1){
                    fprintf(stderr, "cannot fork!\n");
                    return;
                }
                else if (pid2 == 0){
                    //cout << "----------------\n";
                    //cout << array[0] << "\n";
                    if (process_count > MAX_PROCECC_COUNT_TO_FORK){
                        array[0] += non_parallel_summ(0, X->right_);
                    }
                    else{
                        parallel_summ(array, X->right_, process_count);
                    }
                    exit(-1);
                    //cout << array[0] << "\n";
                    //cout << "----------------\n";
                    
                }

                if (pid > 0 && pid2 > 0){
                    return;
                }
                else{
                    exit(-1);
                }
            }
    };
    
}

#endif