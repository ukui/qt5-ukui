#include <QApplication>
#include <QMessageBox>
#include <QMetaEnum>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qputenv("QT_QPA_PLATFORMTHEME", "ukui");

#if 0
    QMessageBox::information(nullptr, "title", "information text", QMessageBox::Ok);
    QMessageBox::information(nullptr, "title", "information text1 "
        "information text2 "
        "information text3 "
        "information text4 "
        "information text5 "
        "information text6 "
        "information text7 "
        "information text8 "
        "information text9 "
        "information text10 "
        "information text11 "
        "information text12 "
        "information text13 "
        "information text14 "
        "information text15 "
        "information text16 "
        "information text17 "
        "information text18 "
        "information text19 "
        "information text20 "
        "information text21 "
        "information text22 "
        "information text23 "
        "information text24 "
        "information text25 "
        "information text26 "
        "information text27 "
        "information text28 "
        "information text29 "
        "information text30 "
        "information text"
        "information text"
        "information text"
        "information text"
        "information text"
        "information text"
        "information text"
        "information text"
        "information text"
        "information text"
        "information text"
        "information text"
        "information text"
        "information text"
        "information text"
        "information text"
        "information text"
        "information text"
        "information text", QMessageBox::Ok);
    QMessageBox::information(nullptr, "title", "information text", QMessageBox::Ok | QMessageBox::Cancel | QMessageBox::Save | QMessageBox::SaveAll);

    //
    QMessageBox::warning(nullptr, "title", "warning text", QMessageBox::Ok);
    QMessageBox::critical(nullptr, "title", "critical text", QMessageBox::Ok);
    QMessageBox::question(nullptr, "title", "question text", QMessageBox::Ok);


    // test button
    QMetaEnum metaEnum = QMetaEnum::fromType<QMessageBox::StandardButtons>();
    for (auto i = 0; i < metaEnum.keyCount(); ++i) {
        if (metaEnum.value(i) < QMessageBox::FirstButton
                || metaEnum.value(i) > QMessageBox::LastButton) {
            continue;
        }

        int ret = QMessageBox::information(nullptr, "title", "测试按钮", metaEnum.value(i));

        qDebug() << "is current button:" << (ret == metaEnum.value(i)) << "  ret:" << ret;
    }
#endif
#if 0

    QMessageBox m;
    m.setText("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    int ret = m.exec();
    qDebug() << (ret == QDialog::Accepted) << " --- " << ret;
#endif

#if 0
    QMessageBox m;
    m.setText("这是中文测试1，中文测试2，中文测试3，中文测试4，中文测试5，中文测试6，中文测试7，中文测试8，中文测试9，中文测试10，中文测试11，中文测试12，中文测试13，中文测试14");
    int ret = m.exec();
    m.setIcon(QMessageBox::Critical);
    m.exec();
    m.setText("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    m.exec();
    qDebug() << (ret == QDialog::Accepted) << " --- " << ret;
#endif

#if 1
    // 一个完整的布局展示相关测试例子
    QMessageBox m;
    m.setText("<h2>测试html是否可以正常显示</h2><p>短字段</p>");
    int ret = m.exec();
    m.setText("<style type='text/css'> h1{color:red;font-size:12;} p{color:blue;font-size:10;}</style><h1>接下来要测试html是否可以正常显示</h1><p>关于HTML显示的测试例子，需要假如一些style之类的字符串来干扰其文本框大小的预估，接下来就是style段</p>");
    ret = m.exec();
    m.setIcon(QMessageBox::Critical);
    m.setText("<style>h1{color:red;}p{color:blue;}</style><h1>接下来要测试html是否可以正常显示</h1><p>关于HTML显示的测试例子，需要假如一些style之类的字符串来干扰其文本框大小的预估，接下来就是style段 + 图标</p>");
    ret = m.exec();
    m.setText("较短的纯文本汉字");
    ret = m.exec();
    m.setText("很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,很长很长的中文字符,");
    ret = m.exec();
    m.setText("english");
    ret = m.exec();
    m.exec();
    m.setText("long long english ... aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    m.exec();
    m.setText("中英文混合 Chinese and English mixed");
    m.exec();
    m.setText("中英文混合中英文混合中英文混合中英文混合中英文混合中英文混合中英文混合中英文混合中英文混合中英文混合中英文混合中英文混合中英文混合中英文混合中英文混合中英文混合 Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.Chinese and English mixed.");
    m.exec();
    qDebug() << (ret == QDialog::Accepted) << " --- " << ret;
#endif


    return a.exec();
}
