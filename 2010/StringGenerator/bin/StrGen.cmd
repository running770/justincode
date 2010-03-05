@REM Author: justin.liu@sinditv.com
@REM StringGenerator ExcelPath SheetName StartColumn EndColumn ExportEncoding OutputFolder
@REM e.g.
@REM StringGenerator test.xls Sheet1 4 11 UTF-8 result

@REM Supported Encoding:
@REM US-ASCII
@REM ISO-8859-1
@REM GB2312
@REM GBK
@REM BIG5
@REM UTF-8
@REM UTF-16
@REM UTF-16LE
@REM UTF-16BE


@REM SET ENCODING=UTF-16
@REM SET ENCODING=GB2312
SET ENCODING=UTF-8
SET INPUT=test.xls
SET SHEETNAME=Sheet1
SET STARTCOL=4
SET ENDCOL=5
SET OUTPUTDIR=output

java -jar StringGenerator.jar %INPUT% %SHEETNAME% %STARTCOL% %ENDCOL% %ENCODING% %OUTPUTDIR%
rename %OUTPUTDIR%\lang.h gmi_lang.h

pause