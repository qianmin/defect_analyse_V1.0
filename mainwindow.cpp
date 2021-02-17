#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/imgproc/types_c.h>
using namespace cv;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //窗口大小不变
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());
    //timer1
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    timer1->start(1000);
    connect(timer1,&QTimer::timeout,this,&MainWindow::mytimer);
    //初始化图片
    show_all_type();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::show_all_type()
{
    //label0
    QImage image0=QImage(".\\template\\A0.png");
    image0 = image0.scaled(ui->label0->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label0->setPixmap(QPixmap::fromImage(image0));
    //label1
    QImage image1=QImage(".\\template\\A1.png");
    image1= image1.scaled(ui->label1->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label1->setPixmap(QPixmap::fromImage(image1));
    //label2
    QImage image2=QImage(".\\template\\A2.png");
    image2 = image2.scaled(ui->label2->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label2->setPixmap(QPixmap::fromImage(image2));

    //label3
    QImage image3=QImage(".\\template\\A3.png");
    image3 = image3.scaled(ui->label3->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label3->setPixmap(QPixmap::fromImage(image3));
    //label4
    QImage image4=QImage(".\\template\\A4.png");
    image4 = image4.scaled(ui->label4->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label4->setPixmap(QPixmap::fromImage(image4));
    //label5
    QImage image5=QImage(".\\template\\A5.png");
    image5 = image5.scaled(ui->label5->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label5->setPixmap(QPixmap::fromImage(image5));

}



void MainWindow::show_img_label_template(Mat src)
{
    QImage qimg4;
    Mat show4;
    cv::resize(src,show4,Size(500,500),0,0,INTER_LINEAR);

    qimg4 = QImage((const unsigned char*)(show4.data),show4.cols,show4.rows,QImage::Format_RGB888);

    ui->label_template->setPixmap(QPixmap::fromImage(qimg4));

    qDebug()<<"template_clicked";
    cv::imshow("nmsl",src);
    cv::waitKey(0);
}
void MainWindow::show_img_label_target(Mat src)
{
//    QImage qimg4;
//    qimg4 = QImage((const unsigned char*)(src.data),src.cols,src.rows,QImage::Format_RGB888);
//    qimg4 = qimg4.scaled(ui->label_template->size());
//    qimg4 = qimg4.scaled(ui->label_template->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
//    ui->label_target->setPixmap(QPixmap::fromImage(qimg4));

//    QImage qimg4;
//    Mat show4;
//    cv::resize(src,show4,Size(500,500),0,0,INTER_LINEAR);

//    qimg4 = QImage((const unsigned char*)(show4.data),show4.cols,show4.rows,QImage::Format_RGB888);
//    qimg4 = qimg4.scaled(ui->label_template->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
//    ui->label_target->setPixmap(QPixmap::fromImage(qimg4));
    QImage qimg4;
    Mat show4;
    cv::resize(src,show4,Size(400,400),0,0,INTER_LINEAR);

    qimg4 = QImage((const unsigned char*)(show4.data),show4.cols,show4.rows,QImage::Format_RGB888);
    qimg4 = qimg4.scaled(ui->label_template->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_target->setPixmap(QPixmap::fromImage(qimg4));
}



void MainWindow::mytimer()
{

    ui->label_time->setText(QString::number(num++));
//    qDebug()<<"nm";
}

void MainWindow::on_pushButton_target_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open Image"),".",tr("Image File (*.jpg *.png *.bmp)"));
    QTextCodec *code = QTextCodec::codecForName("gb18030");
    std::string name = code->fromUnicode(filename).data();//filename.toAscii().data()
//    std::printf(name.to);
    target_img = cv::imread(name,-1);
    if(!target_img.data)
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Image Data Is Null"));
        msgBox.exec();
    }
    else {
       show_img_label_target(target_img);
    }
}


void MainWindow::on_pushButton_match_clicked()
{
//    result=orb_match(template_img,target_img);
//    QString str1;
//    str1= QString::number(result,10,5);//QString::number(a,基底，精度)
//    ui->label_result->setText(str1);

    int final_type=0;
    double final_result=0;
    QString path=".\\template";
    QDir dir(path);
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    for (int i = 0; i < files.size(); ++i)
    {
        QString path_tmp=path;
        path_tmp.append("\\");
        QString one_file = files.at(i);
        QString file_type=one_file.mid(1, 1);
        QString one_file_path=path_tmp.append(one_file);
        qDebug()<<"i"<<i;
        qDebug()<<"one_file_path:"<<one_file_path;
        qDebug()<<"file_type:"<<file_type;

        //开始orb
        double tmp_result;
        int tmp_type=file_type.toInt();
        Mat img=cv::imread(one_file_path.toStdString());
        tmp_result=orb_match(img,target_img);
        qDebug()<<"temp_result"<<tmp_result;
        if(tmp_result>final_result)
        {
            final_result=tmp_result;
            final_type=tmp_type;
        }
        //
        if(i==5)
        {
            final_template_path=one_file_path;
            QString str_final_type=QString::number(final_type);
            final_template_path.replace(12,1,str_final_type);
            qDebug()<<"final_template_path"<<final_template_path;
        }
    }
    //最终展示
    QString str_final_type=QString::number(final_type);
    ui->label_result->setText(str_final_type);


    //match_result
//    Mat tmp_matched_img;
//    cv::cvtColor(matched_img,tmp_matched_img,cv::COLOR_BGR2RGB);
//    QImage  match_qimg(tmp_matched_img.data,tmp_matched_img.cols,tmp_matched_img.rows, tmp_matched_img.step, QImage::Format_RGB888);
//    match_qimg = match_qimg.scaled(ui->label_template->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
//    ui->label_template->setPixmap(QPixmap::fromImage(match_qimg));
    orb_img();
    Mat tmp_matched_img;
    cv::cvtColor(matched_img,tmp_matched_img,cv::COLOR_BGR2RGB);
    QImage  match_qimg(tmp_matched_img.data,tmp_matched_img.cols,tmp_matched_img.rows, tmp_matched_img.step, QImage::Format_RGB888);
    match_qimg = match_qimg.scaled(ui->label_template->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_template->setPixmap(QPixmap::fromImage(match_qimg));

}
double MainWindow::orb_match(Mat src1,Mat src2)
{
    Ptr<ORB> orb = ORB::create();
    std::vector<KeyPoint> kp1, kp2;
    Mat des1, des2;

    orb->detect(src1,kp1);
    orb->detect(src2,kp2);
    orb->compute(src1,kp1,des1);
    orb->compute(src2,kp2,des2);
    //创建一个匹配点数组
    vector<DMatch> matches;
    //创建一个BFMatcher匹配器
    BFMatcher matcher (NORM_HAMMING);
    //调用matcher的match方法进行匹配
    matcher.match(des1, des2, matches);


    //第四步：遍历matches[]数组，找出匹配点的最大距离和最小距离，用于后面的匹配点筛选。
    double min_dist=0, max_dist=0;//定义距离
    for (int i = 0; i < des1.rows; ++i)//遍历
    {
        double dist = matches[i].distance;
        if(dist<min_dist) min_dist = dist;
        if(dist>max_dist) max_dist = dist;
    }

    //第五步：根据最小距离，对匹配点进行筛选，
    std::vector<DMatch> good_matches;
    qint32 num=0;
    for (int j = 0; j < des1.rows; ++j)
    {
        if (matches[j].distance <= max(2*min_dist, 30.0))
        {
            good_matches.push_back(matches[j]);
            num=num+1;
        }
    }
    qint32 all_num;
    for (int j = 0; j < des1.rows; ++j)
    {
        all_num=all_num+1;
    }
//    qDebug("十进制：%d", num);
//    qDebug()<<"到此为止";

    double a,b,r;
    a=num;
    b=100;
    r=a/b;
//    qDebug()<<r;
//第六步：绘制匹配结果
//    Mat img_match;
//    drawMatches(src1, kp1, src2, kp2, matches, img_match);
//    cv::imshow("所有匹配点对", img_match);
//    Mat img_goodmatch;
//    drawMatches(src1, kp1, src2, kp2, good_matches, img_goodmatch);
//    matched_img=img_goodmatch;
    return r;

}

void MainWindow::orb_img()
{
    Mat src1=target_img;
    Mat src2=cv::imread(final_template_path.toStdString(),-1);
    Ptr<ORB> orb = ORB::create();
    std::vector<KeyPoint> kp1, kp2;
    Mat des1, des2;

    orb->detect(src1,kp1);
    orb->detect(src2,kp2);
    orb->compute(src1,kp1,des1);
    orb->compute(src2,kp2,des2);
    //创建一个匹配点数组
    vector<DMatch> matches;
    //创建一个BFMatcher匹配器
    BFMatcher matcher (NORM_HAMMING);
    //调用matcher的match方法进行匹配
    matcher.match(des1, des2, matches);


    //第四步：遍历matches[]数组，找出匹配点的最大距离和最小距离，用于后面的匹配点筛选。
    double min_dist=0, max_dist=0;//定义距离
    for (int i = 0; i < des1.rows; ++i)//遍历
    {
        double dist = matches[i].distance;
        if(dist<min_dist) min_dist = dist;
        if(dist>max_dist) max_dist = dist;
    }

    //第五步：根据最小距离，对匹配点进行筛选，
    std::vector<DMatch> good_matches;
    qint32 num=0;
    for (int j = 0; j < des1.rows; ++j)
    {
        if (matches[j].distance <= max(2*min_dist, 30.0))
        {
            good_matches.push_back(matches[j]);
            num=num+1;
        }
    }
    Mat img_goodmatch;
    drawMatches(src1, kp1, src2, kp2, good_matches, img_goodmatch);
    matched_img=img_goodmatch;
}
