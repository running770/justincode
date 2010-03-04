package Excel;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;

import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;

public class ExcelReader {
	private String mExcelPath = "";
	private String mSheetName;
	private InputStream mISExcel;
	private HSSFWorkbook mWb;
	private HSSFSheet	mSheet;
	
	public	int	mRows;
	
	public ExcelReader(String filePath, String sheet)
	{
		mExcelPath = filePath;
		mSheetName = sheet;
		
		try {
			mISExcel = new FileInputStream(mExcelPath);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		try {
			mWb = new HSSFWorkbook(mISExcel);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		mSheet = mWb.getSheet(mSheetName);
		mRows = mSheet.getLastRowNum() + 1;
		System.out.println("ExcelReader: Total Rows " + mRows);
	}
	
	
	public String ReadCell(int row, int col)
	{
		String strCell = "";
		HSSFRow rowS = mSheet.getRow(row);
		
		if (null == rowS)
			return null;
		
		HSSFCell cell = rowS.getCell(col);
		
		if (null == cell)
			return null;
	
		switch(cell.getCellType())
		{
		case HSSFCell.CELL_TYPE_STRING:
			strCell = cell.getStringCellValue();
			break;
		default:
			break;
		}
		
		return strCell;
	}
	
	public String[] ReadLine(int row, int start, int last)
	{
		String[] lineStr = null;
		
		HSSFRow rowS = mSheet.getRow(row);
		if (null == rowS) return null;
		
		int colStart = (start > 0)?(start):(0);
		int cols = rowS.getLastCellNum();
		int colEnd = (last < cols)?(last):(cols);
		
		lineStr = new String[colEnd - colStart + 1];
		int cnt=0;
		for(int i=colStart; i<=colEnd; i++)
		{
			HSSFCell cell = rowS.getCell(i);
			if (null == cell)
				lineStr[cnt++] = "";
			else
				lineStr[cnt++] = cell.toString();
		}
		
		return lineStr;
	}
	
}
