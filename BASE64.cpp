const BYTE Base64ValTab[65]= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
 
#define AVal(x) Base64ValTab[x]
 
BSTR Base64Encode(char * pInput)
{   
    CFile ImageFile;
    ImageFile.Open(pInput,CFile::modeRead);
    int iSrcLen = ImageFile.GetLength();
 
    unsigned char * szImageBin;
    szImageBin = new unsigned char[iSrcLen];
    ImageFile.Read((void*)szImageBin,iSrcLen);
 
    char *base64code;
    int nRemain = iSrcLen % 3;
    int nLeast= 0;
 
    if(nRemain != 0)
    {
        nLeast=1;
    }
    base64code = new char[(iSrcLen/3+nLeast)*4 + 1];    
 
    int loop = 0;
    int iDstLen = 0;
     
    loop = iSrcLen/3;
 
    int datavalue;
 
    for (int i =0 ; i < loop; i++)
    { 
        datavalue = ((szImageBin[3*i] << 16) | (szImageBin[3*i+1] << 8) | szImageBin[3*i+2]);
        for(int j = 0; j < 4; j++) 
        {
            base64code[i*4+j] = AVal(((datavalue >> 6*(3-j)) & 0x3F));    
        }
    }
     
    iDstLen = i*4;
     
    if (nRemain == 1)
    {
        i = iSrcLen-1;
        int a1 = ((szImageBin[i] & 0xFC)>>2)&0xFF;
        int a2 = ((szImageBin[i] & 0x03)<<4)&0xFF;
         
        base64code[iDstLen++] = AVal(a1);
        base64code[iDstLen++] = AVal(a2);
        base64code[iDstLen++] = '=';
        base64code[iDstLen++] = '=';
        base64code[iDstLen] = 0x00;
    }
    else if (nRemain == 2)
    {
        i = iSrcLen-2;
     
        int a1 = (szImageBin[i] & 0xFC)&0xFF;
        int a2 = ((szImageBin[i] & 0x03)<<4 | (szImageBin[i+1] & 0xF0)>>4)&0xFF;
        int a3 = ((szImageBin[i+1] & 0x0F)<<2 )&0xFF;
         
        base64code[iDstLen++] = AVal(a1);
        base64code[iDstLen++] = AVal(a2);
        base64code[iDstLen++] = AVal(a3);
        base64code[iDstLen++] = '=';
        base64code[iDstLen] = 0x00;
    }
    else
    {
        base64code[iDstLen] = 0x00;
    }
 
    CString szBaseCode(base64code);
    free(szImageBin);
    free(base64code);
    ImageFile.Close();
    return szBaseCode.AllocSysString();
}
