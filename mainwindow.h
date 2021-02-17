#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include<QTextCodec>
#include<QMessageBox>
#include<QTimer>
#include<QDebug>
#include<QFileDialog>
using namespace cv;
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer * timer1;
    QTimer * timer2;
    void mytimer();
    int num=0;//计时器数字
    //自定义处理处理函数
    void show_all_type();//展示所有模板
    void show_img_label_template(Mat src);//展示最终的结果
    void show_img_label_target(Mat src);//展示打开的图片
    double orb_match(Mat src1,Mat src2);//orb检测函数,返回相似度数值
    void orb_img();//orb绘图函数
    //自定义处理处理函数
    //自定义槽函数变量
    Mat target_img; //打开的图片
    double result; //最终匹配的最大相似度
    Mat matched_img;//结果展示
    QString final_template_path;//最终匹配到的模板位置
    //自定义槽函数变量


private slots:
    void on_pushButton_target_clicked();

    void on_pushButton_match_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
