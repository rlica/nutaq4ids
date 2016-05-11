{
   gROOT->Reset();
 
//   Create the chain as above
   TChain chain("ids");
   chain.Add("Run073.root");
   chain.Add("Run074.root");
   chain.Add("Run075.root");
   chain.Add("Run070.root");
   chain.Add("Run069.root");
   chain.Add("Run068.root");
   chain.Add("Run063.root");
   chain.Add("Run065.root");
   }