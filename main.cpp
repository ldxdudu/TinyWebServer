#include "config.h"

int main(int argc, char *argv[])
{
    //需要修改的数据库信息,登录名,密码,库名
    string user = "root";
    string passwd = "123456";
    string databasename = "webTest";

    //命令行解析
    Config config; // 可在构造函数离更改默认参数
    config.parse_arg(argc, argv); // 根据输入的参数，对默认参数进行修改

    WebServer server;

    //初始化
    server.init(config.PORT, user, passwd, databasename, config.LOGWrite, 
                config.OPT_LINGER, config.TRIGMode,  config.sql_num,  config.thread_num, 
                config.close_log, config.actor_model);
    

    //日志
    server.log_write(); // 初始化日志模块, 默认打开日志模块, 默认为同步写入方式

    //数据库
    server.sql_pool(); //初始化数据库连接池, 初始化数据库读取表

    //线程池
    server.thread_pool(); // 生成线程池

    //触发模式
    server.trig_mode(); // 设置listenfd和connfd的epoll触发方式，默认使用LT + L

    //监听
    server.eventListen(); // 生成监听套接字，注册epoll事件，初始化定时器

    //运行
    server.eventLoop(); // 通过epoll监听socket和定时器管道套接字的读写，根据情况进行处理，服务器的主线程循环

    return 0;
}