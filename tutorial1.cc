void tutorial1(){
  TString filname = "228K6.0V.root"; //ファイル名
  TFile *f = new TFile(filname,"OPEN");//228K6.0V.rootというファイルを開く
  TTree *tree = (TTree*)f->Get("tree");//treeというTTreeを取り出す
  
  Float_t waveforms[2][1024];//TTreeのBranchの中身を入れる変数を用意
  Int_t T;//変数名はBranch名と同じでもいいし違っても良い
  Float_t overV;//型に注意、tree内のover_voltageを入れるつもりなのでFloat_tを用意した。
  Float_t biasV;//Branchの方はtree->Print()で確認できる。


  tree->SetBranchAddress("ADC",waveforms);//変数とBranchを紐づける。

  tree->SetBranchAddress("Temperature",&T);//変数のポインタをわたすこと。
  tree->SetBranchAddress("over_voltege",&overV);//over_voltageでなくてover_voltegeになっているのはroot作ったときのミス
  tree->SetBranchAddress("V",&biasV);

  //この段階で変数とBranchの紐づけをした。しかし変数になにか値がはいっているわけではない。イベントを指定することで各変数に各Branchの値が入る。
  //イベントの指定:tree->GetEntry(i);
  //でi番目のイベントの値が各変数に入る。

  tree->GetEntry(332);//event332の値が各変数に入った。
  
  //event332の波形をプロットしてみる。
  Float_t time[1024];
  for(Int_t i=0;i<1024;i++)time[i]=i;
  TGraph *g = new TGraph(1024,time,waveforms[0]);
  g->Draw("APL");

  //tree->GetEntries();//で全イベント数を取得できる。

  TH1D *h = new TH1D("","",500,0,1000);
  Int_t nevent;
  nevent = tree->GetEntries();
  for(Int_t i=0;i<nevent;i++){  
    tree->GetEntry(i);
    Float_t x=0;
    for(Int_t j=400;j<800;j++){
      x += waveforms[0][j];
    }
    h->Fill(x);    
  }
}
