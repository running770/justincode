package MyLog;

import java.util.Vector;

import 	org.apache.log4j.Logger;
import org.apache.log4j.PropertyConfigurator;

public class JuLog {
	private static Logger log;
	private final static String LOGCONFIG = "src\\MyLog\\log4j.properties";
	
	private void Log4jInit()
	{
		log = Logger.getLogger(JuLog.class);
		PropertyConfigurator.configure(LOGCONFIG);
	}
	private Vector<Object> vlogs;
	public JuLog()
	{
		Log4jInit();
	}
	public void console(Object o)
	{
		log.debug(o);
	}
	
	
	public JuLog(int capacities)
	{
		this.vlogs = new Vector<Object>(capacities);
		Log4jInit();
	}
	
	public void add(Vector<Object> logs)
	{
		this.vlogs.addAll(logs);
	}
	public void add(Object log)
	{
		this.vlogs.add(log);
	}
	public void add(Object[] logs)
	{
		this.vlogs.add(logs);
	}

	public void outAll()
	{
		for(int i=0; i<this.vlogs.size(); i++)
		{
			this.out(i);
		}
	}
	//Reverse
	public void outAllR()
	{
		for(int i=this.vlogs.size()-1; i>=0; i--)
		{
			this.out(i);
		}
	}
	public void out(int index)
	{
		log.debug(this.vlogs.get(index));
	}

}
