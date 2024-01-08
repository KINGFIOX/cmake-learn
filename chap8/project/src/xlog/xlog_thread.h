//////////////////////////////////  @��Ȩ˵��  //////////////////////////////////////////////////
///						Jiedi(China nanjing)Ltd.
/// @��Ȩ˵�� ����Ϳγ̰�Ȩ���Ĳܿ���ӵ�в��Ѿ���������Ȩ���˴��������Ϊѧϰ�ο���������Ŀ��ʹ�ã�
/// �γ����漰����������Դ����������������Ӧ����Ȩ
/// �γ�Դ�벻����ֱ��ת�ص������Ĳ��ͣ�������������ƽ̨�������������������߿γ̡�
/// �γ����漰����������Դ����������������Ӧ����Ȩ  @@
/////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////  Դ��˵��  //////////////////////////////////////////////////
/// ��Ŀ����: CMake��������c++��Ŀ
/// ����   : 			    http://blog.csdn.net/jiedichina
/// ��Ѷ����			    https://jiedi.ke.qq.com/
/// ѧ��				    ���� �Ĳܿ�
/// ���Ŀ���			    http://cppds.com
/// CMake�ֲ�    	        http://cmake.org.cn
/// �����������γ�qqȺ ��296249312����ͬѧ����
/// ��ӭ���Ĳܿ���ʦ��΢�ţ�cppxcj
/// �������Ŀ���Ⱥ��296249312��ֱ����ϵȺ��ͷ����ؿγ�����
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// �γ̽���qqȺ296249312 //////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////// COMMENT ///////////////////////////////////////////////

#ifndef XLOG_THREAD_H
#define XLOG_THREAD_H

#include "xlog.h"
#include <fstream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>


_XCPP_NAMESPACE_

class XLogThread : public XWrite {
public:
    bool Init(const char* log_path, const char* filename);
    int Write(const char* msg);
    void Start();
    void Stop();
    XLogThread() { }
    virtual ~XLogThread()
    {
        Stop();
    }

private:
    void Run();
    std::ofstream ofs_;
    std::thread th_;
    std::mutex mux_;
    std::string log_path_;
    std::queue<std::string> msgs_;
    std::condition_variable cv_;
    bool is_exit_ = false;
};

_END_NAMESPACE_

#endif
