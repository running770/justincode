package SindiTV;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintStream;
import java.io.UnsupportedEncodingException;

import Excel.ExcelReader;

public class FormatLang {

	private String fileExtName = ".lng"; 
	private ExcelReader mExcel;
	private String mEncoding = Encoding.UTF_16BE;
	private String mFolderPath = "output";
	private OutputStream[] mOutputSr;
	private PrintStream[] mPrintSr;
	private String[] mTitles;
	
	private int colStart = 0;
	private int colEnd = 0xFF;
	
	public FormatLang(ExcelReader excel, String folder, int start, int end, String encoding)
	{
		this.mExcel = excel;
		this.mFolderPath = folder;
		
		this.colStart = start;
		this.colEnd = end;
		this.mEncoding = encoding;
		
		CreateOutputStream();
	}
	
	public void CreateOutputStream()
	{
		mTitles = mExcel.ReadLine(0, this.colStart, this.colEnd);
		mOutputSr = new OutputStream[mTitles.length];
		mPrintSr = new PrintStream[mTitles.length];
		
		for(int i=0; i<mTitles.length; i++)
		{
			try {
				String fileName = "";
				if (mTitles[i].isEmpty())
					fileName = this.mFolderPath + "/" + i + "_" +  mEncoding + fileExtName;
				else
					fileName = this.mFolderPath + "/" + mTitles[i] + "_" + mEncoding + fileExtName;
				mOutputSr[i] = new FileOutputStream(fileName);
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			mPrintSr[i] = new PrintStream(mOutputSr[i]);
		}
		
		
	}
	
	
	public void Output(int col) throws UnsupportedEncodingException
	{
		int index = col - this.colStart;
		mPrintSr[index].println(FormatHeader.GetFileComment("RESOURCE"));
		for (int row=1; row<mExcel.mRows; row++)
		{
			String sCellName = mExcel.ReadCell(row, 0);
			if (null == sCellName || sCellName.isEmpty())
				continue;

			mPrintSr[index].printf("{ %-40s,", sCellName);
		
			
			String sCellValue = mExcel.ReadCell(row, col);
			if (null == sCellValue)
			{
				sCellValue = "";
			}
			
			String outputStr = "";
			byte[] encodingBytes =  sCellValue.getBytes(mEncoding);;
			
			if ( mTitles[index].equals("English") 
			 ||	(!mEncoding.equalsIgnoreCase(Encoding.UTF_8)
			 && !mEncoding.equalsIgnoreCase(Encoding.UTF_16LE)))
			{// ANSI
				//outputStr = new String(encodingBytes, mEncoding);
				mPrintSr[index].print(" \"");
				try {
					mPrintSr[index].write(encodingBytes);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				mPrintSr[index].print("\"");
				for(int i=0; i<40-encodingBytes.length; i++)
				{
					mPrintSr[index].print(" ");
				}
				mPrintSr[index].print("},");
				
			}
			else
			{
				for(int i=0; i<encodingBytes.length; i++)
				{
					outputStr += String.format("\\x%02X", encodingBytes[i]);
				}
				mPrintSr[index].printf(" %-40s},", "\""+outputStr+"\"");
			}
			
			mPrintSr[index].println();
			
		}
		mPrintSr[index].printf("\n{ %-40d, \"%-40s\" },\n", -1, " ");
		mPrintSr[index].flush();
		mPrintSr[index].close();
	}
	
	public void Output() throws UnsupportedEncodingException
	{
		for(int i=this.colStart; i<=this.colEnd; i++)
		{
			Output(i);
		}
	}
	
}
