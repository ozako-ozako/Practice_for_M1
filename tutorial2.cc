

//hist.txtの中身をTTreeに詰めるスクリプト
void tutorial2(){
 
  
  TTree *tree = new TTree("tree","tree");//treeとうTTreeを用意

  Float_t charge;//tree詰めたい変数定義
  Float_t x;
  
  tree->Branch("charge",&charge,"charge/F");//BranchでTTreeにBranchを追加できる.ここでchargeとtreeが紐付けされている。


  ifstream fin("hist.txt");//"hist.txt"をopen
  while(fin >> charge){//"hist.txt"の中身を1行ずつchargeにいれる。whileは繰り返しで、hist.txtの最後の行まで
    
    tree->Fill();//これでBranchに使用している変数(charge)の「現在の」値がtreeに詰められる。
  }

  

  TString name = "hist.root";//新しくできるrootファイルの名前
  TFile *fout = new TFile(name,"recreate");
  tree->Write();//foutというrootファイルにtreeを書き込む
  fout->Close();//閉じる

}
