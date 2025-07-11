#include <iostream>
#include <stdexcept>

using namespace std;
#define eleType int

// 链表节点结构体
struct ListNode {
    eleType data;//数据域
    ListNode* next;//指针域
    ListNode(eleType x) : data(x), next(NULL) {}
};

// 单向链表类
class LinkedList {
private:
    ListNode* head;
    int size;

public:

    LinkedList() : head(NULL), size(0) {}    // 链表构造函数
    ~LinkedList();
    void insert(int i, eleType value);       // 在链表的第 i 个位置，插入一个值为 value 的结点
    void remove(int i);                      // 删除链表第 i 个位置的结点    
    ListNode* find(eleType value);           // 查找链表中值为 value 的结点
    ListNode* get(int i);                    // 获取链表中第 i 个位置的结点
    void update(int i, eleType value);       // 修改链表中第 i 个位置的结点的值为 value
    void print();                            // 打印链表内容
};

LinkedList::~LinkedList() {//使用完后，析构函数删除内存
    ListNode* curr = head;//定义一个当前指针并初始化为头指针，从头开始遍历
    while (curr != NULL) {//只要不为空，就继续循环
        ListNode* temp = curr;//创造一个临时指针保存当前指针
        curr = curr->next;//当前指针指向下一个
        delete temp;//删除临时，继续循环。因为当前持续指向下一个，所以会一直删除，直到为null即全删完
    }
}

void LinkedList::insert(int i, eleType value) {//i为要插入的索引
    if (i < 0 || i > size) {//判断是否越界
        throw std::out_of_range("Invalid position");
    }
    ListNode* newNode = new ListNode(value);//创造一个新结点，动态分配内存
    if (i == 0) {// 在表头插入
        newNode->next = head;//新结点的指针域指向头结点
        head = newNode;//新结点成为头结点
    }
    else {
        ListNode* curr = head;//当前结点初始化为头结点，从头开始遍历
        for (int j = 0; j < i - 1; j++) {//if已经判断为1的情况。现在i从1开始i如果等于1，循环不会执行，i等于1其实就是当前结点还是头结点
            curr = curr->next;//当前指向下一个，即不断向后推进
        }
        // 在第 i 个位置插入
        newNode->next = curr->next;//新结点的指针域指向当前节点的下一个结点
        curr->next = newNode;//当前结点的指针域变为新节点，完成插入
    }//即A->B插入C，先让C指向A指向的方向，即C指向B，然后让A指向C，即完成A->C->B
    size++;//链表长度加1
}

void LinkedList::remove(int i) {
    if (i < 0 || i >= size) {
        throw std::out_of_range("Invalid position");
    }
    if (i == 0) {// 删除表头结点
        ListNode* temp = head;//临时指针保存头结点
        head = head->next;//头结点的下一个结点成为头结点，即删除了头结点
        delete temp;//删除临时指针
    }
    else {
        ListNode* curr = head;//当前结点从头开始遍历，找到要删除的结点的前一个结点
        for (int j = 0; j < i - 1; j++) {
            curr = curr->next;
        }
        // 删除第 i 个结点。A->B->C，删除B，先找到A
        ListNode* temp = curr->next;//找到的当前结点为要删除的结点的前一个结点A，所以当前的指针域指向的是要删除的B。先用临时指针存起来
        curr->next = temp->next;//临时的指针域指向的是C，当前的指针域即A的指针域，把临时的指针域赋给当前的指针域，即让A指向C
        delete temp;//删除临时，即变成A->C
    }
    size--;
}

ListNode* LinkedList::find(eleType value) {//找值
    ListNode* curr = head;//从头开始找
    while (curr != NULL && curr->data != value) {//不是空并且当前数据域不是要找的值，即没找到。空说明是头（因为初始化头位空值），当前数据域等于值说明找到了
        curr = curr->next;//向后遍历继续找
    }
    return curr;//找到了跳出循环返回当前指针
}

ListNode* LinkedList::get(int i) {//找索引
    if (i < 0 || i >= size) {//判断非法
        throw std::out_of_range("Invalid position");
    }
    ListNode* curr = head;
    for (int j = 0; j < i; j++) {//索引是按顺序的编号，所以用for找
        curr = curr->next;
    }
    return curr;
}

void LinkedList::update(int i, eleType value) {//更新值
    if (i < 0 || i >= size) {
        throw std::out_of_range("Invalid position");
    }
    get(i)->data = value;//把值赋给找到的索引的结点的数据域，即完成了更新
}

void LinkedList::print() {//从头开始往后打印
    ListNode* curr = head;
    while (curr != NULL) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

int main() {
    LinkedList list;
    list.insert(0, 10);
    list.insert(1, 20);
    list.insert(2, 30);
    list.insert(3, 40);
    list.insert(4, 50);

    std::cout << "Initial list: ";
    list.print();

    std::cout << "Removing the second node: ";
    list.remove(1);
    list.print();

    std::cout << "Updating the third node to 60: ";
    list.update(2, 60);
    list.print();

    std::cout << "Finding the value of the fourth node: ";
    std::cout << list.find(30)->data << std::endl;

    std::cout << "Getting the third node: ";
    std::cout << list.get(2)->data << std::endl;

    return 0;
}