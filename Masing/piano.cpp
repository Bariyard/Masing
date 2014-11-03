#include "piano.h"
#include "ui_piano.h"

#include "sndfile.hh"
//#include ""


Piano::Piano(QWidget *parent)
    : QWidget(parent)
{
	piano_ui.setupUi(this);
	createPianoKeyAction();
	//struct_ringBuffer();
}

Piano::~Piano()
{

}

void Piano::createPianoKeyAction(){
	piano_ui.pushButton_24->setStatusTip("C1");
	piano_ui.pushButton_25->setStatusTip("C#1");
	piano_ui.pushButton_26->setStatusTip("D1");
	piano_ui.pushButton_27->setStatusTip("D1#");
	piano_ui.pushButton_28->setStatusTip("E1");
	piano_ui.pushButton_29->setStatusTip("F1");
	piano_ui.pushButton_30->setStatusTip("F#1");
	piano_ui.pushButton_31->setStatusTip("G1");
	piano_ui.pushButton_32->setStatusTip("G#1");
	piano_ui.pushButton_33->setStatusTip("A1");
	piano_ui.pushButton_34->setStatusTip("A#1");
	piano_ui.pushButton_35->setStatusTip("B1");
	piano_ui.pushButton_36->setStatusTip("C2");
	piano_ui.pushButton_37->setStatusTip("C#2");
	piano_ui.pushButton_38->setStatusTip("D2");
	piano_ui.pushButton_39->setStatusTip("D#2");
	piano_ui.pushButton_40->setStatusTip("E2");
	piano_ui.pushButton_41->setStatusTip("F2");
	piano_ui.pushButton_42->setStatusTip("F#2");
	piano_ui.pushButton_43->setStatusTip("G2");
	piano_ui.pushButton_44->setStatusTip("G#2");
	piano_ui.pushButton_45->setStatusTip("A2");
	piano_ui.pushButton_46->setStatusTip("A#2");
	piano_ui.pushButton_47->setStatusTip("B2");
	piano_ui.pushButton_48->setStatusTip("C3");
	piano_ui.pushButton_49->setStatusTip("C#3");
	piano_ui.pushButton_50->setStatusTip("D3");
	piano_ui.pushButton_51->setStatusTip("D#3");
	piano_ui.pushButton_52->setStatusTip("E3");
	piano_ui.pushButton_53->setStatusTip("F3");
	piano_ui.pushButton_54->setStatusTip("F#3");
	piano_ui.pushButton_55->setStatusTip("G3");
	piano_ui.pushButton_56->setStatusTip("G#3");
	piano_ui.pushButton_57->setStatusTip("A3");
	piano_ui.pushButton_58->setStatusTip("A#3");
	piano_ui.pushButton_59->setStatusTip("B3");
	piano_ui.pushButton_60->setStatusTip("C4");
	piano_ui.pushButton_61->setStatusTip("C#4");
	piano_ui.pushButton_62->setStatusTip("D4");
	piano_ui.pushButton_63->setStatusTip("D#4");
	piano_ui.pushButton_64->setStatusTip("E4");
	piano_ui.pushButton_65->setStatusTip("F4");
	piano_ui.pushButton_66->setStatusTip("F#4");
	piano_ui.pushButton_67->setStatusTip("G4");
	piano_ui.pushButton_68->setStatusTip("G#4");
	piano_ui.pushButton_69->setStatusTip("A4");
	piano_ui.pushButton_70->setStatusTip("A#4");
	piano_ui.pushButton_71->setStatusTip("B4");

	piano_ui.pushButton_72->setStatusTip("C5");
	piano_ui.pushButton_73->setStatusTip("C#5");
	piano_ui.pushButton_74->setStatusTip("D5");
	piano_ui.pushButton_75->setStatusTip("D#5");
	piano_ui.pushButton_76->setStatusTip("E5");
	piano_ui.pushButton_77->setStatusTip("F5");
	piano_ui.pushButton_78->setStatusTip("F#5");
	piano_ui.pushButton_79->setStatusTip("G5");
	piano_ui.pushButton_80->setStatusTip("G#5");
	piano_ui.pushButton_81->setStatusTip("A5");
	piano_ui.pushButton_82->setStatusTip("A#5");
	piano_ui.pushButton_83->setStatusTip("B5");


	//connect(ui.pushButton_24, SIGNAL(released()),this,SLOT(piano_release()));
/*	connect(piano_ui.pushButton_25, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_25, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_26, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_26, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_27, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_27, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_28, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_28, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_29, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_29, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_30, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_30, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_31, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_31, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_32, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_32, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_33, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_33, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_34, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_34, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_35, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_35, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_36, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_36, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_37, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_37, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_38, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_38, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_39, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_39, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_40, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_40, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_41, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_41, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_42, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_42, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_43, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_43, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_44, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_44, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_45, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_45, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_46, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_46, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_47, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_47, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_48, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_48, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_49, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_49, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_50, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_50, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_51, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_51, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_52, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_52, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_53, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_53, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_54, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_54, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_55, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_55, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_56, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_56, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_57, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_57, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_58, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_58, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_59, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_59, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_60, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_60, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_61, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_61, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_62, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_62, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_63, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_63, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_64, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_64, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_65, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_65, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_66, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_66, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_67, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_67, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_68, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_68, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_69, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_69, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_70, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_70, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_71, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_71, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_72, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_72, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_73, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_73, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_74, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_74, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_75, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_75, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_76, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_76, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_77, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_77, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_78, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_78, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_79, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_79, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_80, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_80, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_81, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_81, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_82, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_82, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_83, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_83, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_84, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_84, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_85, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_85, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_86, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_86, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_87, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_87, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_88, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_88, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_89, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_89, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_90, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_90, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_91, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_91, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_92, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_92, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_93, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_93, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_94, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_94, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_95, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_95, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_96, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_96, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_97, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_97, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_98, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_98, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_99, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_99, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_100, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_100, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_101, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_101, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_102, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_102, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_103, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_103, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_104, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_104, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_105, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_105, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_106, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_106, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_107, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_107, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_108, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_108, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_109, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_109, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_110, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_110, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_111, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_111, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_112, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_112, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_113, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_113, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_114, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_114, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_115, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_115, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_116, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_116, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_117, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_117, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_118, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_118, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_119, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_119, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_120, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_120, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_121, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_121, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_122, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_122, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_123, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_123, SIGNAL(released()),this,SLOT(piano_release()));
	connect(ui.pushButton_124, SIGNAL(pressed()),this,SLOT(piano_press()));
	connect(ui.pushButton_124, SIGNAL(released()),this,SLOT(piano_release()));


*/
}


void Piano::piano_press(){

}

void Piano::piano_release(){
	//free(piano_sound.data_frame);
	//Pa_StopStream( audioStream );
}



