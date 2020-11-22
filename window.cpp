#include "window.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <vector>
#include <QString>
#include <verticaloption.h>
#include <string>
#include <QMessageBox>
#include <iostream>
#include <QInputDialog>
#include <QDir>
#include <regex>

void my_popen( const std::string& cmd ,std::vector<std::string>& out ){
    FILE*  fp;
    const int sizebuf=1234;
    char buff[sizebuf];
    out = std::vector<std::string> ();
    if ((fp = popen (cmd.c_str (), "r"))== NULL){

}
   std:: string cur_string = "";
    while (fgets(buff, sizeof (buff), fp)) {
        cur_string += buff;
}
    out.push_back (cur_string.substr (0, cur_string.size() -1));
    pclose(fp);
}

int get_abs(int a)
{
      if(a<0)
          return -a;

      return a;
}

std::string commandcreator(std::string command, std::string password)
{
       return std::string("echo ")+password+std::string(" | sudo -S sleep 0.1 && ")+std::string("sudo ")+command;
}

std::string password = ""; //sudo password


 void setfunction(int *values)
{
     std::vector<std::string> params ;

     params.push_back(" --core ");
     params.push_back(" --cache ");
     params.push_back(" --uncore ");
     params.push_back(" --analog ");
     params.push_back(" --gpu ");

 std::string write = "undervolt --force ";

for(int i=0;i<(int)params.size();i++)
{
    if(values[i]<=0)
    params[i] +=  std::to_string(*(values+i));
    else
     params[i] += "+"+std::to_string(*(values+i));

    write+= params[i];

}

    write = commandcreator(write,password);
    std::vector<std::string> output;
       my_popen(write, output);
       for (std::vector<std::string>::iterator itr = output.begin();
           itr != output.end();
           ++itr) {
             std::cout << *itr << std::endl;
           }

}

void readfunction()
{
     std::vector<std::string> out ;
   my_popen(commandcreator("intel-undervolt read",password),out);

   QMessageBox msgBox;
   msgBox.setText(QString::fromStdString(out[0]));
    msgBox.exec();
   /*
   std::regex rgx(".[0-9]*\.?[0-9]*");

    std::smatch m;
   std::regex_search(out[0],m,rgx);

   for(int i =0;i<(int)m.size();i++)
      std::cout << "match: " << m[i] << '\n';
  */



}



Window::Window(QWidget *parent) :
 QWidget(parent)
 {
 // Set size of the window

    int *x = new int[5];

      bool ok;
       password = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                            tr("Please enter sudo password:"), QLineEdit::Normal,
                                            QDir::home().dirName(), &ok).toStdString();

    std::vector<QString> values ;

    QPushButton *setvalues = new QPushButton;
    QPushButton *readvalues = new QPushButton;

     setvalues->setText("SET");
     readvalues->setText("READ");

   connect(setvalues, &QPushButton::clicked, [x]() { setfunction(x) ;});
   connect(readvalues, &QPushButton::clicked, []() { readfunction() ;});

    values.push_back("cpu      ");
    values.push_back("cache  ");
    values.push_back("uncore");
    values.push_back("analog");
    values.push_back("gpu     ");

  QVBoxLayout *main = new QVBoxLayout(this);


   for(int i=0;i<(int)values.size();i++)
   main->addLayout(new verticaloption(values[i],&x[i]));

     main->addWidget(setvalues);
     main->addWidget(readvalues);

 this->show();

}
