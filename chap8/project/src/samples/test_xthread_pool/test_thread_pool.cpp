// -*- coding: GB18030 -*-
//////////////////////////////////  @版权说明  //////////////////////////////////////////////////
///						Jiedi(China nanjing)Ltd.
/// @版权说明 代码和课程版权有夏曹俊所拥有并已经申请著作权，此代码可用作为学习参考并可在项目中使用，
/// 课程中涉及到的其他开源软件，请遵守其相应的授权
/// 课程源码不可以直接转载到公开的博客，或者其他共享平台，不可以用以制作在线课程。
/// 课程中涉及到的其他开源软件，请遵守其相应的授权  @@
/////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////  源码说明  //////////////////////////////////////////////////
/// 项目名称: CMake构建大型c++项目
/// 博客   : 			    http://blog.csdn.net/jiedichina
/// 腾讯课堂			    https://jiedi.ke.qq.com/
/// 学浪				    搜索 夏曹俊
/// 老夏课堂			    http://cppds.com
/// CMake手册    	        http://cmake.org.cn
/// ！！！请加入课程qq群 【296249312】与同学交流
/// 欢迎加夏曹俊老师的微信：cppxcj
/// 加入老夏课堂群【296249312】直接联系群里客服下载课程资料
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// 课程交流qq群296249312 //////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////// COMMENT ///////////////////////////////////////////////

// test_thread_pool.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "xthread_pool.h"
#include <iostream>

using namespace std;
using namespace xcpp;
int main()
{
    //{
    //    packaged_task<string()> task(
    //        []() {
    //            return "test packaged_task";
    //        });
    //    auto fut = task.get_future();
    //    task();
    //    cout<<"fut.get() = "<<fut.get()<<endl;
    //}
    // getchar();
    XThreadPool pool;
    pool.Start(16); // 启动16个线程
    auto re = pool.Exec([](int i) {
        cout << "test pool exec1" << endl;
        return 201;
    },
        1234);
    cout << "return =" << re.get() << endl;
    re = pool.Exec([](int i) {
        cout << "test pool exec2" << endl;
        return 202;
    },
        1234);
    cout << "return =" << re.get() << endl;
    re = pool.Exec([](int i) {
        cout << "test pool exec3" << endl;
        return 203;
    },
        1234);
    cout << "return =" << re.get() << endl;
    /*pool.Exec([]
        {
            cout << "test pool exec2" << endl;
            return 202;
        });
    pool.Exec([] (int index)
        {
            cout << index<< "test pool exec" << endl;
            return 203;
        },101
    );
    */
    this_thread::sleep_for(300ms);
    pool.Stop();
    return 0;
    // getchar();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧:
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
