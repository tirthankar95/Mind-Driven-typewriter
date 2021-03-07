library(readxl)
sheetName<- c("A","AA","EE","UU","Ae","AeA","O")
names(sheetName)<-c(0:6)
delimiter<-c("NULL")
N=5

convToInt<-function(ch){
  return(names(sheetName[match(ch,sheetName)]))
}

minimizeData<-function(vec){
  n=length(vec);vec1<-c(length=n/N)
  tmp=0;cnt=1
  for (i in 1:n){
    tmp=tmp+vec[i]
    if (i %% N==0){
      vec1[cnt]=tmp/N
      tmp=0;cnt=cnt+1
    }
  }
  return(vec1)
}

createNeuralNetData<-function(path){
  for (i in 1:7){
    XX <- read_excel(path,sheet = sheetName[i])
    YY <- convToInt(ch<-sheetName[i])
    XX_change <- as.matrix(XX)
    
    #Normalizing the matrix column-wise
    XX_change<-t(XX_change)
    maxVal<-apply(XX_change,1,max)
    XX_change<-XX_change/maxVal
    XX_change<-t(XX_change)
    
    XX_change <- as.numeric(as.vector(XX_change))
    XX_change <- minimizeData(XX_change)
    write(XX_change,file="InputDL.txt",append=TRUE,sep="\n")
    write(delimiter,file="InputDL.txt",append=TRUE,sep="\n")
    write(as.numeric(YY),file="OutputDL.txt",append=TRUE,sep="\n")
  }
}

createNeuralNetData(path<-"~/Desktop/Backup/Project/FinalData/Subject1/trial1.xlsx")
createNeuralNetData(path<-"~/Desktop/Backup/Project/FinalData/Subject1/trial2.xlsx")
createNeuralNetData(path<-"~/Desktop/Backup/Project/FinalData/Subject1/trial3.xlsx")
createNeuralNetData(path<-"~/Desktop/Backup/Project/FinalData/Subject1/trial4.xlsx")
