#include "threshexport.h"
#include "ui_threshexport.h"

threshExport::threshExport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::threshExport)
{
    ui->setupUi(this);
    //hide();
}

threshExport::~threshExport()
{
    delete ui;
}

void threshExport::threshold()
{

}

void threshExport::on_buttonBox_accepted()
{
   // boost::iostreams::mapped_file_sink *mem_ofile;
    boost::iostreams::mapped_file_sink mem_ofile;
    boost::iostreams::mapped_file_params params;



    float *outdat;
    float thresh = ui->lineEdit->text().toFloat();
    float te; //temp
    long long numfr = getNumFrames();
    long long fn,x,y;
    QFileDialog filedialog;


    filedialog.setFileMode(QFileDialog::AnyFile);
    params.new_file_size = (long long)(numfr*266*396*4);;
    params.length = (long long)(numfr*266*396*4);
    params.offset =0;
    //params.mode = std::ios::out;
    params.flags = boost::iostreams::mapped_file::readwrite;
    //params.


    try
    {
        //QString fileName = filedialog.getOpenFileName(NULL, "Open File","","");
        QString fileName = filedialog.getSaveFileName(NULL, "File to Save to:","","");
        params.path = fileName.toStdString();
       // mem_ofile = new boost::iostreams::mapped_file_sink();
       // mem_ofile->open(params);
       // mem_ofile.open(mapped_file_sink(fileName.toStdString()));
        mem_ofile.open(params);


        outdat = (float *)(mem_ofile.data());

       // for( fn = 0;fn<numfr;fn++)
        for( fn = 0;fn<numfr;fn++)
        {
            for( x=0;x<=395;x++)
            {
                for( y=0;y<=265;y++)
                {

                    te = float(getImdat(fn*266*396+y*396+x));
                    if((te>thresh)&&(y!=0)&&(y!=130)&&(y!=263))
                    {
                        *(outdat+fn*266*396+y*396+x)=te;
                    }
                    else
                    {
                        *(outdat+fn*266*396+y*396+x)=0;
                    }
                }
            }
        }

        mem_ofile.close();
        //delete mem_ofile;
    }
    catch(std::bad_alloc)
    {

    }

}

void threshExport::on_buttonBox_rejected()
{
    this->hide();
}
