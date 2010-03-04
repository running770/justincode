package SindiTV;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.text.SimpleDateFormat;
import java.util.Date;

import Excel.ExcelReader;

public class FormatHeader {
	private ExcelReader mExcel;
	private OutputStream mOutputSr;
	private PrintStream mPrintSr;
	public FormatHeader(ExcelReader excel, String fileName)
	{
		mExcel = excel;
		try {
			mOutputSr = new FileOutputStream(fileName);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		mPrintSr = new PrintStream(mOutputSr);
	}
	
	public void Output()
	{
		String strCell = "";
		
		mPrintSr.print(GetFileComment("HEADER"));
		
		mPrintSr.println("#ifndef _LANG_H_");
		mPrintSr.println("#define _LANG_H_");
		
		for (int i=1; i<mExcel.mRows; i++)
		{
			strCell = mExcel.ReadCell(i, 0);
			if (null == strCell || strCell.isEmpty())
			{
				mPrintSr.println("");
			}
			else
			{
				mPrintSr.printf("#define %-40s 0x%04X\n", strCell,i+1);
			}
		}
		
		mPrintSr.println("#endif /* _LANG_H_ */");
		mPrintSr.close();
	}
	
	public static String GetFileComment(String type)
	{
		String comments = "";
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		
		comments += "/**************************************************************************************************/";
		comments += "\n";
		comments += "/* THIS IS AN AUTOMATICALLY GENERATED " + type + " FILE */";
		comments += "\n";
		comments += "/* THIS FILE SHOULD BE INCLUDED AS LANGUAGE RESOURCE BASE OF FUJITSU SMARTMPEG SDK */";
		comments += "\n";
		comments += "/* COPYRIGHT (c) SINDITV PTE LTD 2007 - 2010 */";
		comments += "\n";
		comments += "/* Created: " + dateFormat.format(new Date()) + "*/";
		comments += "\n";
		comments += "/**************************************************************************************************/";
		comments += "\n";
		
		return comments;
	}
}
