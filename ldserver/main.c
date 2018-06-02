#include <stdio.h>
#include <sys/socket.h>


#define HTTP_MAX_REQUEST_LINE 8190
#define HTTP_MAX_PARAM_SIZE 256

//请求报头的参数
typedef struct {
    char* key;
    char* value;
}Param;

//请求行
typedef struct {
    char* method;
    char* path;
    float version;
} RequestLine;

//Http请求结构
typedef struct {
    RequestLine* req;
    Param* reqHeader;
    char* requestBody;
} Request;

//响应行
typedef struct {
    float version;
    int statusCode;
    char* reason;
} ResponseLine;

//响应
typedef struct {
    ResponseLine* res;
    Param* resHeader;
}ResponseHeader;

Request* getRequestHeader(int fd) {

}
int main() {
    printf("Hello, World!\n");
    return 0;
}