#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �����������
typedef enum {
    INT,
    FLOAT,
    STRING
} ParamType;

// ��������ṹ��
typedef struct {
    ParamType type;
    void* value;
} Param;

// �����¼��ṹ��
typedef struct {
    void (*callback)(int, Param*);  // �ص�����ָ��
    int paramCount;                 // ��������
    Param* params;                  // ��������
} Event;

// ��ʼ�������ṹ��
void initializeParam(Param* param, ParamType type, void* value) {
    param->type = type;
    param->value = value;
}

// ��ʼ���¼��ṹ��
void initializeEvent(Event* event, void (*callback)(int, Param*), int paramCount, Param* params) {
    event->callback = callback;
    event->paramCount = paramCount;

    // ���Ʋ�������
    event->params = malloc(paramCount * sizeof(Param));
    memcpy(event->params, params, paramCount * sizeof(Param));
}

// �ͷ��¼��ṹ����Դ
void releaseEvent(Event* event) {
    free(event->params);
}

// �ص�����ʾ��
void callbackFunction(int paramCount, Param* params) {
    printf("Received %d parameters:\n", paramCount);
    for (int i = 0; i < paramCount; ++i) {
        switch (params[i].type) {
            case INT:
                printf("Type: INT, Value: %d\n", *((int*)params[i].value));
                break;
            case FLOAT:
                printf("Type: FLOAT, Value: %f\n", *((float*)params[i].value));
                break;
            case STRING:
                printf("Type: STRING, Value: %s\n", (char*)params[i].value);
                break;
            default:
                printf("Unknown type\n");
        }
    }
}

int main() {
    // ׼������
    int intValue = 42;
    float floatValue = 3.14;
    char stringValue[] = "Hello";

    // ������������
    Param params[] = {
        {INT, &intValue},
        {FLOAT, &floatValue},
        {STRING, stringValue}
    };

    // �����¼�����ʼ��
    Event myEvent;
    initializeEvent(&myEvent, callbackFunction, sizeof(params) / sizeof(params[0]), params);

    // �����¼������ûص�����
    raiseEvent(&myEvent);

    // �ͷ���Դ
    releaseEvent(&myEvent);

    return 0;
}
