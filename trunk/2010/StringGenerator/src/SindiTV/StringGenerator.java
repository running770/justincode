package SindiTV;

import java.io.File;
import java.io.UnsupportedEncodingException;

import Excel.ExcelReader;

public class StringGenerator {
	public static void main(String[] args)
	{

		String excelPath;
		String sheetName = "Sheet1";
		int startCol = 4;
		int endCol = 11;
		String encoding = Encoding.UTF_8;
		String outputDir = "result";
		if (0 == args.length)
		{
			System.out.println("StringGenerator ExcelPath SheetName StartColumn EndColumn ExportEncoding OutputFolder");
			System.out.println("e.g.");
			System.out.println("StringGenerator test.xls Sheet1 4 11 UTF-8 result");
			System.out.println("\nSupported Encoding:");
			System.out.println(Encoding.US_ASCII);
			System.out.println(Encoding.ISO_8859_1);
			System.out.println(Encoding.GB2312);
			System.out.println(Encoding.GBK);
			System.out.println(Encoding.BIG5);
			System.out.println(Encoding.UTF_8);
			System.out.println(Encoding.UTF_16);
			System.out.println(Encoding.UTF_16LE);
			System.out.println(Encoding.UTF_16BE);
			return;
		}
		else if (6 == args.length)
		{
			excelPath 	= args[0];
			sheetName 	= args[1];
			startCol 	= Integer.parseInt(args[2]);
			endCol 		= Integer.parseInt(args[3]);
			encoding 	= args[4];
			outputDir 	= args[5];
		}
		else
		{
			excelPath 	= args[0];
		}

		File dFile = new File(outputDir);
		if (!dFile.exists() || !dFile.isDirectory())
		{
			if (!dFile.mkdirs())
			{
				System.out.println("Create output directory failed!");
			}
			
		}
		
		
		ExcelReader excel = new ExcelReader(excelPath, sheetName);
		
		FormatHeader header = new FormatHeader(excel,  outputDir + "/lang.h");
		header.Output();
		
		FormatLang languages = new FormatLang(excel, outputDir, startCol-1, endCol-1, encoding);
		try {
			languages.Output();
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		System.out.println("finished!\n");
		
	}
}
