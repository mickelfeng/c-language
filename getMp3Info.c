PHP_FUNCTION(getMp3Info) {
FILE *fp;
char *filename;
int filename_len;
long longBytes,temp,bit_rate=128;
if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l",&filename, &filename_len,&bit_rate) == FAILURE)
{
RETURN_NULL();
}
if (!filename_len )
{
php_error_docref(NULL TSRMLS_CC, E_WARNING,"Invalid filename ");
RETURN_FALSE;
}
fp = fopen(filename,"rb");
if (!fp)
{
php_error_docref(NULL TSRMLS_CC, E_WARNING,"Unable to open %s",filename);
RETURN_FALSE;
}
fseek(fp,0,SEEK_SET);
fseek(fp,0,SEEK_END);
longBytes=ftell(fp);// longBytes文件度
temp=(longBytes/(1024*bit_rate))*8;
//printf("%d",(temp/bit_rate)*8);
ZVAL_LONG(return_value, temp);
} 
