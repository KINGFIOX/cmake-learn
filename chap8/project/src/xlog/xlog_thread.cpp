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

#include "xlog_thread.h"
#include <chrono>
using namespace std;
_XCPP_NAMESPACE_

bool XLogThread::Init(const char* log_path, const char* filename)
{
    // is_log_init = false;
    this->log_path_ = log_path;
    // �����ã����ڸ�Ϊ������־�ļ�
    string logfile = log_path;
    logfile += filename;
    ofs_.open(logfile, ios::app);
    if (ofs_)
        return true;
    return false;
}

int XLogThread::Write(const char* msg)
{
    {
        lock_guard<mutex> lock(mux_);
        msgs_.push(msg);
    }
    cv_.notify_one();
    return 0;
}

void XLogThread::Start()
{
    th_ = thread(&XLogThread::Run, this);
}
void XLogThread::Stop()
{
    if (!th_.joinable())
        return;
    is_exit_ = true;
    cv_.notify_all();
    th_.join();
}

void XLogThread::Run()
{
    for (;;) {
        string msg;
        unique_lock<mutex> lock(mux_);
        cv_.wait(lock, [this] {
            return is_exit_ || !msgs_.empty();
        });
        while (!msgs_.empty()) {
            msg = move(msgs_.front());
            msgs_.pop();
            lock.unlock();
            ofs_ << msg << endl;
            cout << msg << endl;
            lock.lock();
        }
        if (is_exit_)
            break;
    }
}

_END_NAMESPACE_