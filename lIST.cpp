#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 动态列表结构体
typedef struct {
    int *data;       // 指向实际数据的指针
    int size;        // 当前元素个数
    int capacity;    // 总容量
} DynList;

// 初始化动态列表
void dynListInit(DynList *list) {
    list->size = 0;
    list->capacity = 4;
    list->data = (int *)malloc(list->capacity * sizeof(int));
}

// 扩容
void dynListResize(DynList *list) {
    list->capacity *= 2;
    int *newData = (int *)malloc(list->capacity * sizeof(int));
    memcpy(newData, list->data, list->size * sizeof(int));
    free(list->data);
    list->data = newData;
}

// 添加元素到末尾
void dynListAdd(DynList *list, int val) {
    if (list->size >= list->capacity) {
        dynListResize(list);
    }
    list->data[list->size++] = val;
}

// 删除指定下标元素
void dynListDel(DynList *list, int idx) {
    if (idx < 0 || idx >= list->size) return;
    for (int i = idx; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->size--;
}

// 打印列表
void dynListPrint(DynList *list) {
    printf("size=%d, capacity=%d\n", list->size, list->capacity);
    for (int i = 0; i < list->size; i++) {
        printf("%d ", list->data[i]);
    }
    printf("\n\n");
}

// 释放内存
void dynListFree(DynList *list) {
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

int main() {
    DynList list;
    dynListInit(&list);

    dynListAdd(&list, 10);
    dynListAdd(&list, 20);
    dynListAdd(&list, 30);
    dynListAdd(&list, 40);
    dynListAdd(&list, 50);  // 触发扩容
    dynListPrint(&list);

    dynListDel(&list, 2);   // 删除下标2的元素
    dynListPrint(&list);

    dynListFree(&list);
    return 0;
}

