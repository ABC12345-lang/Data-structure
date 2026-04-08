#include <stdio.h>
#include <stdlib.h>

// 动态列表结构体
typedef struct {
    int *data;       // 指向实际存储数据的数组
    int size;        // 当前已使用的元素个数
    int capacity;    // 总容量（最多能存多少）
} DynamicList;

// 1. 初始化动态列表
void InitList(DynamicList *list) {
    // 初始分配 4 个 int 空间
    list->data = (int *)malloc(sizeof(int) * 4);
    list->size = 0;
    list->capacity = 4;
}

// 2. 扩容函数（容量不够时自动扩容）
int ExpandList(DynamicList *list) {
    // 新容量 = 原来 2 倍
    int new_cap = list->capacity * 2;
    int *new_data = (int *)realloc(list->data, sizeof(int) * new_cap);

    if (new_data == NULL) {
        printf("扩容失败\n");
        return -1;
    }

    list->data = new_data;
    list->capacity = new_cap;
    printf("已扩容至 %d\n", new_cap);
    return 0;
}

// 3. 尾部添加元素
int Append(DynamicList *list, int val) {
    // 满了就扩容
    if (list->size >= list->capacity) {
        if (ExpandList(list) == -1)
            return -1;
    }

    list->data[list->size] = val;
    list->size++;
    return 0;
}

// 4. 指定位置插入元素
int Insert(DynamicList *list, int pos, int val) {
    if (pos < 0 || pos > list->size) {
        printf("位置非法\n");
        return -1;
    }

    if (list->size >= list->capacity) {
        if (ExpandList(list) == -1)
            return -1;
    }

    // 从后往前挪，腾出位置
    for (int i = list->size; i > pos; i--) {
        list->data[i] = list->data[i - 1];
    }

    list->data[pos] = val;
    list->size++;
    return 0;
}

// 5. 删除指定位置元素
int Delete(DynamicList *list, int pos) {
    if (pos < 0 || pos >= list->size) {
        printf("位置非法\n");
        return -1;
    }

    // 从前往后覆盖
    for (int i = pos; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
    }

    list->size--;
    return 0;
}

// 6. 获取指定位置元素
int Get(DynamicList *list, int pos) {
    if (pos < 0 || pos >= list->size) {
        printf("位置非法\n");
        return -1;
    }
    return list->data[pos];
}

// 7. 打印整个列表
void PrintList(DynamicList *list) {
    for (int i = 0; i < list->size; i++) {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

// 8. 销毁列表，释放内存
void DestroyList(DynamicList *list) {
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

// 测试主函数
int main() {
    DynamicList list;
    InitList(&list);

    Append(&list, 10);
    Append(&list, 20);
    Append(&list, 30);
    Append(&list, 40);
    Append(&list, 50);  // 触发扩容

    Insert(&list, 2, 25);
    Delete(&list, 1);

    PrintList(&list);

    DestroyList(&list);
    return 0;
}

