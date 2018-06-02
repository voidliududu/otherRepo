#include<iostream>
#include<fstream>
using namespace std;


//声明感知器类
class Sensor;

//数据集类
class Data{
private:
    float x[10][2];
    float y[10];
    int size;
friend class Sensor;
public:
    void readData(string filename) {
        ifstream file;
        file.open(filename);
        size = 0;
        while(!file.eof())
        {
            file >> x[size][0] >> x[size][1] >> y[size];
            size++;
        }
        file.close();
    } 
    int getSize() {
        return size;
    }
    float* getX(int i) {
        return x[i];
    }
    float getY(int i) {
        return y[i];
    }
};

class Sensor{
private:
    float w[2];
    float b;
    float eta;

    //前向传播 y = f( w1 * x1 + w2 * x2 + b )
    float do_cacu(float x[]) {
        float y = 0;
        for(int i = 0; i < 2 ; i++) {
            y += w[i]*x[i];
        }
        y += b;
        return activation(y);
    }

    //激活函数
    float activation(float y) {
        return y >= 0 ? 1 : 0;
    }
public:
    //初始化函数
    Sensor(float eta) {
        w[0] = 0.1;
        w[1] = -0.1;
        b = 0.2;
        this->eta = eta;
    }

    //预测数据
    float predict(float x[]) {
        return do_cacu(x);
    }

    //拟合数据
    float fit(Data data, int epoch) {
        int length = data.size;
        int O = 0;
        for(int count = 0; count < epoch; count++) {
            for(int i = 0; i < length; i ++) {
                O = do_cacu(data.x[i]);
                for(int j = 0 ;j < 2; j++)
                    w[j] = w[j] + eta * (data.y[i] - O) * data.x[i][j];
                b = b + eta * (data.y[i] - O);
            }
        }
    }

    //输出感知的参数
    void print() {
        cout<<"w = "<<w[0]<<","<<w[1]<<endl;;
        cout<<"b = "<<b<<endl;
    }

};



int main(int argc, char const *argv[])
{
    //创建训练集
    Data data;
    //从文件读入训练集数据
    data.readData("data.dat");
    //创建感知器，设置学习率
    Sensor s(0.1);
    //训练数据，设置趟数
    s.fit(data,500);
    s.print();
    //输出训练集的预报结果
    cout<<"测试结果\n";
    float* x;
    for(int i = 0; i < data.getSize(); i++) {
        x = data.getX(i);
        cout<<x[0]<<","<<x[1]<<"==>"<<s.predict(data.getX(i))<<endl;
    }
    return 0;
}
































// const int num = 10;//数据集大小（估计）
// int count = 0;//数据集大小（实际）
// bool flag = true;//是否误分类
// int max_step = 500;

// struct DataSet
// {
//     double x1;
//     double x2;
//     int y;
// }data[num];
// float sensor(float x1, float x2) ;
// double eta = 0.5;//学习率
// double w[2] = {0.01, -0.01}, b = 0.01;//定义参数

// //从文件中读取数据
// void readData()
// {
//     ifstream file;
//     file.open("data.dat");
//     int i = 0;
//     while(!file.eof())
//     {
//         file >> data[i].x1 >> data[i].x2 >> data[i].y;
//         i++;
//         count++;
//     }
//     file.close();
// }

// int main() {
//     int i = 0;
//     int n = 0;
//     readData();
//     cout << "数据集为" << endl;
//     for(i = 0; i < count; i++)
//     {
//         cout << data[i].x1 << "  " << data[i].x2 << "  " << data[i].y << endl;
//     }
//     int step = 0;
//     while(step < max_step) {

//         for(int i = 0; i < count; i++) {
//             float o = sensor(data[i].x1,data[i].x2);
//             w[0] = w[0] + eta * (data[i].y - o) * data[i].x1;
//             w[1] = w[1] + eta * (data[i].y - o) * data[i].x2;
//             b = b + eta * (data[i].y - o);
//                  step++;
//         }
//      }
//     cout << endl << "结果：" << endl;
//     cout << "w = " << w[0] << ", " << w[1] << " " << "b=" << b << endl;
//     cout << "迭代次数：" << step << endl;
//     for(int i = 0; i < count; i++) {
//         cout<<data[i].x1<<","<<data[i].x2<<"==>"<<sensor(data[i].x1,data[i].x2)<<endl;
//     }
// }

// float sensor(float x1, float x2) {
//     float y = 0;
//     y = w[0] * x1 + w[1] * x2 + b;
//     return y > 0.5 ? 1: 0;
// }

