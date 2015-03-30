package web;

import java.awt.AWTException;
import java.awt.Robot;
import java.awt.event.KeyEvent;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import org.openqa.selenium.By;
import org.openqa.selenium.TimeoutException;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.firefox.FirefoxBinary;
import org.openqa.selenium.firefox.FirefoxDriver;
import org.openqa.selenium.firefox.FirefoxProfile;
import org.openqa.selenium.firefox.internal.ProfilesIni;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.Select;
import org.openqa.selenium.support.ui.WebDriverWait;

import control_structure.Defines;

public class Client {
	WebDriver driver;
	
	public Client(String baseurl, String profile, String firefox_executable){
		if(profile != null){
			ProfilesIni fprofile = new ProfilesIni();
			FirefoxProfile ffprofile = fprofile.getProfile(profile);
			driver = new FirefoxDriver(ffprofile);
		} else{
			FirefoxProfile ffprofile = new FirefoxProfile();
			FirefoxBinary ffbinary = new FirefoxBinary(new File(firefox_executable));
			ffprofile.setPreference("webdriver.firefox.bin", firefox_executable);
			driver = new FirefoxDriver(ffbinary, ffprofile);
		}
		driver.get(baseurl);
	}
	
	public void getPage(String URL){
		driver.get(URL);
	}
	
	public String getPageSource(){
		return driver.getPageSource();
	}
	
	public String getPageText(long key_press_delay) throws AWTException{
		Robot r = new Robot();
		r.keyPress(KeyEvent.VK_CONTROL);
		Defines.delay(key_press_delay);
		r.keyPress(KeyEvent.VK_A);
		Defines.delay(key_press_delay);
		r.keyRelease(KeyEvent.VK_A);
		Defines.delay(key_press_delay);
		r.keyPress(KeyEvent.VK_C);
		Defines.delay(key_press_delay);
		r.keyRelease(KeyEvent.VK_C);
		Defines.delay(key_press_delay);
		r.keyRelease(KeyEvent.VK_CONTROL);
		
		return Defines.clipboard_to_string();
	}
	
	public void close(){
		driver.close();
	}
	
	public void printPage(){
		System.out.println(driver.getPageSource());
	}
	public void printPage(String filename){
		try{
			BufferedWriter bw = new BufferedWriter(new FileWriter(filename, false));
			bw.write(driver.getPageSource());
			bw.close();
		} catch(IOException e){
			System.out.println("Error! Could not write to file " + filename);
		}
	}
	
	public String getPageTitle(){
		return driver.getTitle();
	}
	
	public void sendKeys(String element, String value, boolean name){
		WebElement el = null;
		if(name){
			el = driver.findElement(By.name(element));
		} else{
			el = driver.findElement(By.id(element));
		}
		el.sendKeys(value);
	}
	
	public void submit(String element, boolean name){
		WebElement el = null;
		if(name){
			el = driver.findElement(By.name(element));
		} else{
			el = driver.findElement(By.id(element));
		}
		el.submit();
	}
	
	public void click(String element, boolean name){
		WebElement el = null;
		if(name){
			el = driver.findElement(By.name(element));
		} else{
			el = driver.findElement(By.id(element));
		}
		el.click();
	}
	

	public void clickLink(String findFormat, String field){
		if(findFormat.trim().equals("cssSelector")){
			field = "a[href*=\'" + field + "\']";
			driver.findElement(By.cssSelector(field)).click();
		}
	}
	
	public void acceptAlert(){
		driver.switchTo().alert().accept();
	}
	
	public boolean islogin(){
		String title = driver.getTitle();
		if(title.contains("TWiki login"))
			return true;
		return false;
	}
	
	public boolean checkForAlert(int time_wait){
		try{
			WebDriverWait wait = new WebDriverWait(driver, time_wait);
			if(wait.until(ExpectedConditions.alertIsPresent()) == null)
				return false;
			else
				return true;
		} catch(TimeoutException e){
			//alert wait timeout
			return false;
		}
	}
	
	public void setSelectOption(String path_to_select, String value_to_set){
		Select select = new Select(driver.findElement(By.xpath(path_to_select)));
		select.selectByValue(value_to_set);
	}
	
	public void login(String username, String password){
        WebElement query = driver.findElement(By.name("username"));
        query.sendKeys(username);

        WebElement pass = driver.findElement(By.name("password"));
        pass.sendKeys(password);
        
        pass.submit();
	}
}
