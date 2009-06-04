package MyLog;

import java.util.Date;
import java.util.Vector;

public class MsfTestLog {
	//class item
	private class LogItem{
		//constant
		private final int ITEMCAPACITIES = 10;
		//viriable
		private Vector<Object> m_logs;
		public int length = 0;
		
		public LogItem()
		{
			LogInit(ITEMCAPACITIES);
		}
		public LogItem(int capacities)
		{
			LogInit(capacities);
		}
		public void LogInit(int capacities)
		{
			m_logs = new Vector<Object>(capacities);
		}
		public void add(Object o)
		{
			m_logs.add(o);
			length = m_logs.size();
		}
		public Object get(int index)
		{
			return m_logs.get(index);
		}
		
	}//end class item
	//frameworkVersion, backofficeVersion, projectVersion
	//Time, <space line>, item labels
	private final int HEADER_LINES = 6;

	private Vector<String> origin_methods;
	private LogItem[] logs;
	
	public MsfTestLog(String featurette)
	{
		GetMethods();
		InitData();
	}
	public MsfTestLog(String featurette, String[] systemInfo)
	{
		GetMethods();
		InitData();
		addHeader(systemInfo);
	}
	public void GetMethods()
	{
//		orgin_methods = MethodList.GetMethods(featurette);
	}
	public void InitData()
	{
		logs = new LogItem[HEADER_LINES+origin_methods.size()];
	}
	public void addHeader(String[] systemInfo)
	{
		String[] infoHeader = {"FrameworkVersion", "BackofficeVersion", "ProjectVersion"};
		int row = 0;
		//system informations: 3 lines
		for(row=0; row<infoHeader.length; row++)
		{
			logs[row].add(infoHeader[row]);
			logs[row].add(systemInfo[row]);
		}
		//time: 1 line
		Date date = new Date();
		logs[row].add("Testing Time:");
		logs[row].add(date.toLocaleString());
		
		//space line
		row++;
		logs[row].add(" ");
		//featurette testing results
		row++;
		String[] resultHeader = {"FEATURETTE", "METHOD", "RESULT", "STATUS", "REQUEST", "RESPONSE", "ERROR"};
		for(int i=0; i<resultHeader.length; i++)
		{
			logs[row].add(resultHeader[i]);
		}
	}
	
	private final int INDEX_OF_METHOD = 1;
	public void add(String[] rowData)
	{
		add(rowData[INDEX_OF_METHOD], rowData);
	}
	public void add(int index, String[] rowData)
	{
		for(int i=0; i<rowData.length; i++)
		{
			logs[index].add(rowData[i]);
		}
	}
	public void add(String key, String[] rowData)
	{
		int row = origin_methods.indexOf(key);
		add(row, rowData);
	}
	public String[][] to2DArray()
	{
		return null;
	}
	public static void Write2Excel(MsfTestLog log)
	{
		String[][] data = log.to2DArray();
	}
}
