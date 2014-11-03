#include "history.h"

History::History(QWidget *parent)
    : QDialog(parent),noteOn(0), amplitude(0),countTry(0),totalPercent(0),
      prevNoteFreq(0),
      currentNoteFreq(0) ,
      nextNoteFreq(0),
      ratio(0),
      prevFreq(0),

      summation(0)
{
	ui.setupUi(this);
	for(int i = 0; i < 84;i++){
		notenum[i][0] = 0; //count correct
		notenum[i][1] = 0; //count try this note
		notenum[i][2] = 0; //percent correct
	}
	clear();

	connect(ui.clearButton, SIGNAL(clicked()),SLOT(clearAction()));
	connect(ui.closeButton, SIGNAL(clicked()),SLOT(closeAction()));
}


void History::clear(){

	for(int i = 0; i < 84;i++){
		notenum[i][0] = 0;
		notenum[i][1] = 0;
		notenum[i][2] = 0;
	}

	countTry = 0;
	amplitude = 0;
	totalPercent = 0;
	ui.countTryLCDBox->display(countTry);
	ui.totalLCDBox->display(totalPercent);

	ui.count_24->display(notenum[24][0]);
		ui.count_25->display(notenum[25][0]);
		ui.count_26->display(notenum[26][0]);
		ui.count_27->display(notenum[27][0]);
		ui.count_28->display(notenum[28][0]);
		ui.count_29->display(notenum[29][0]);
		ui.count_30->display(notenum[30][0]);
		ui.count_31->display(notenum[31][0]);
		ui.count_32->display(notenum[32][0]);
		ui.count_33->display(notenum[33][0]);
		ui.count_34->display(notenum[34][0]);
		ui.count_35->display(notenum[35][0]);
		ui.count_36->display(notenum[36][0]);
		ui.count_37->display(notenum[37][0]);
		ui.count_38->display(notenum[38][0]);
		ui.count_39->display(notenum[39][0]);
		ui.count_40->display(notenum[40][0]);
		ui.count_41->display(notenum[41][0]);
		ui.count_42->display(notenum[42][0]);
		ui.count_43->display(notenum[43][0]);
		ui.count_44->display(notenum[44][0]);
		ui.count_45->display(notenum[45][0]);
		ui.count_46->display(notenum[46][0]);
		ui.count_47->display(notenum[47][0]);
		ui.count_48->display(notenum[48][0]);
		ui.count_49->display(notenum[49][0]);
		ui.count_50->display(notenum[50][0]);
		ui.count_51->display(notenum[51][0]);
		ui.count_52->display(notenum[52][0]);
		ui.count_53->display(notenum[53][0]);
		ui.count_54->display(notenum[54][0]);
		ui.count_55->display(notenum[55][0]);
		ui.count_56->display(notenum[56][0]);
		ui.count_57->display(notenum[57][0]);
		ui.count_58->display(notenum[58][0]);
		ui.count_59->display(notenum[59][0]);
		ui.count_60->display(notenum[60][0]);
		ui.count_61->display(notenum[61][0]);
		ui.count_62->display(notenum[62][0]);
		ui.count_63->display(notenum[63][0]);
		ui.count_64->display(notenum[64][0]);
		ui.count_65->display(notenum[65][0]);
		ui.count_66->display(notenum[66][0]);
		ui.count_67->display(notenum[67][0]);
		ui.count_68->display(notenum[68][0]);
		ui.count_69->display(notenum[69][0]);
		ui.count_70->display(notenum[70][0]);
		ui.count_71->display(notenum[71][0]);
		ui.count_72->display(notenum[72][0]);
		ui.count_73->display(notenum[73][0]);
		ui.count_74->display(notenum[74][0]);
		ui.count_75->display(notenum[75][0]);
		ui.count_76->display(notenum[76][0]);
		ui.count_77->display(notenum[77][0]);
		ui.count_78->display(notenum[78][0]);
		ui.count_79->display(notenum[79][0]);
		ui.count_80->display(notenum[80][0]);
		ui.count_81->display(notenum[81][0]);
		ui.count_82->display(notenum[82][0]);
		ui.count_83->display(notenum[83][0]);

}

void History::note_recieve(int midiNum,float prevFreq,float curFreq,float nextFreq){
	noteOn = midiNum;
	prevNoteFreq = prevFreq/100.;
	currentNoteFreq = curFreq/100. ;
	nextNoteFreq = nextFreq/100.;
	switch(midiNum){
	case 24:{ 	ui.count_24->display(notenum[24][0]);}break;
	case 25:{ 	ui.count_25->display(notenum[25][0]);}break;
	case 26:{ 	ui.count_26->display(notenum[26][0]);}break;
	case 27:{ 	ui.count_27->display(notenum[27][0]);}break;
	case 28:{ 	ui.count_28->display(notenum[28][0]);}break;
	case 29:{ 	ui.count_29->display(notenum[29][0]);}break;
	case 30:{ 	ui.count_30->display(notenum[30][0]);}break;
	case 31:{ 	ui.count_31->display(notenum[31][0]);}break;
	case 32:{ 	ui.count_32->display(notenum[32][0]);}break;
	case 33:{ 	ui.count_33->display(notenum[33][0]);}break;
	case 34:{ 	ui.count_34->display(notenum[34][0]);}break;
	case 35:{ 	ui.count_35->display(notenum[35][0]);}break;
	case 36:{ 	ui.count_36->display(notenum[36][0]);}break;
	case 37:{ 	ui.count_37->display(notenum[37][0]);}break;
	case 38:{ 	ui.count_38->display(notenum[38][0]);}break;
	case 39:{ 	ui.count_39->display(notenum[39][0]);}break;
	case 40:{ 	ui.count_40->display(notenum[40][0]);}break;
	case 41:{ 	ui.count_41->display(notenum[41][0]);}break;
	case 42:{ 	ui.count_42->display(notenum[42][0]);}break;
	case 43:{ 	ui.count_43->display(notenum[43][0]);}break;
	case 44:{ 	ui.count_44->display(notenum[44][0]);}break;
	case 45:{ 	ui.count_45->display(notenum[45][0]);}break;
	case 46:{ 	ui.count_46->display(notenum[46][0]);}break;
	case 47:{ 	ui.count_47->display(notenum[47][0]);}break;
	case 48:{ 	ui.count_48->display(notenum[48][0]);}break;
	case 49:{ 	ui.count_49->display(notenum[49][0]);}break;
	case 50:{ 	ui.count_50->display(notenum[50][0]);}break;
	case 51:{ 	ui.count_51->display(notenum[51][0]);}break;
	case 52:{ 	ui.count_52->display(notenum[52][0]);}break;
	case 53:{ 	ui.count_53->display(notenum[53][0]);}break;
	case 54:{ 	ui.count_54->display(notenum[54][0]);}break;
	case 55:{ 	ui.count_55->display(notenum[55][0]);}break;
	case 56:{ 	ui.count_56->display(notenum[56][0]);}break;
	case 57:{ 	ui.count_57->display(notenum[57][0]);}break;
	case 58:{ 	ui.count_58->display(notenum[58][0]);}break;
	case 59:{ 	ui.count_59->display(notenum[59][0]);}break;
	case 60:{ 	ui.count_60->display(notenum[60][0]);}break;
	case 61:{ 	ui.count_61->display(notenum[61][0]);}break;
	case 62:{ 	ui.count_62->display(notenum[62][0]);}break;
	case 63:{ 	ui.count_63->display(notenum[63][0]);}break;
	case 64:{ 	ui.count_64->display(notenum[64][0]);}break;
	case 65:{ 	ui.count_65->display(notenum[65][0]);}break;
	case 66:{ 	ui.count_66->display(notenum[66][0]);}break;
	case 67:{ 	ui.count_67->display(notenum[67][0]);}break;
	case 68:{ 	ui.count_68->display(notenum[68][0]);}break;
	case 69:{ 	ui.count_69->display(notenum[69][0]);}break;
	case 70:{ 	ui.count_70->display(notenum[70][0]);}break;
	case 71:{ 	ui.count_71->display(notenum[71][0]);}break;
	case 72:{ 	ui.count_72->display(notenum[72][0]);}break;
	case 73:{ 	ui.count_73->display(notenum[73][0]);}break;
	case 74:{ 	ui.count_74->display(notenum[74][0]);}break;
	case 75:{ 	ui.count_75->display(notenum[75][0]);}break;
	case 76:{ 	ui.count_76->display(notenum[76][0]);}break;
	case 77:{ 	ui.count_77->display(notenum[77][0]);}break;
	case 78:{ 	ui.count_78->display(notenum[78][0]);}break;
	case 79:{ 	ui.count_79->display(notenum[79][0]);}break;
	case 80:{ 	ui.count_80->display(notenum[80][0]);}break;
	case 81:{ 	ui.count_81->display(notenum[81][0]);}break;
	case 82:{ 	ui.count_82->display(notenum[82][0]);}break;
	case 83:{ 	ui.count_83->display(notenum[83][0]);}break;
	}


}

void History::clearAction(){
	clear();
}

void History::closeAction(){
	this->close();
}

void History::keepHistory(float inAmp,float detectedFreq){

	if(inAmp > 0.12){
			countTry+=1;
			notenum[noteOn][1] += 1;
	}
		amplitude = inAmp;
		if((ratio<0.3)&&(fabs(detectedFreq - currentNoteFreq) < 10)){
			notenum[noteOn][0] += 1;
		}
	ui.countTryLCDBox->display(countTry);
	calculateTotalPercent();
	calculateTotalPercent_pernote();
}


void History::sumNoteCount(){

	summation = 0;
	for(int i = 24; i < 84;i++){
		summation += notenum[i][0] ;
	}

}

void History::calculateTotalPercent(){
	if(countTry == 0){totalPercent = 0; return;}
	totalPercent = summation/(countTry*1.) *100;

	ui.totalLCDBox->display(totalPercent);
}

void History::calculateTotalPercent_pernote(){
	if(notenum[noteOn][0] == 0 ||notenum[noteOn][1] == 0){
		notenum[noteOn][2] = 0.00;
		return;
	}

	notenum[noteOn][2] = (float)(notenum[noteOn][0]/notenum[noteOn][1])*100.;
}
