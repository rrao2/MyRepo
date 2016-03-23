# -*- coding: utf-8 -*-
"""
Created on Wed Dec 09 20:02:05 2015

@author: Rohini

""" 
# Code to retrieve the HTML of all the resumes listed under the link as mentioned below
import urllib2,urllib,re,sys,time,os
browser=urllib2.build_opener()
browser.addheaders=[('User-agent', 'Mozilla/5.0')]
#create new file to store resumes
directory="Indeed Resumes" 
if not os.path.exists(directory):
    os.makedirs(directory)
#open file to get resume urls    
f=open('indeed.','w')
#to navigate page after page     
page = 1
count = 0
while(page==1):
    url = 'http://www.indeed.com/resumes?q=%22data+scientist%22&co=US&start='+str(50*count)
    count=count+1
    try:
        response=browser.open(url)
        time.sleep(2)
    except Exception as e:
        error_type, error_obj, error_info = sys.exc_info()
        break
#read the html    
    myHTML = response.read()
    print "page: "+str(count)
    if "The page you are looking for was not found." in myHTML: #if page not found
        print myHTML
        break

    urls=re.finditer('<a target="_blank" data-tn-link href="(.+?)" rel="nofollow" class="app_link" itemprop="url" itemprop="name">(.+?)</a>',myHTML)
    urlnum = 0
    for url1 in urls:
        urlnum=urlnum+1
        thisURL = url1.group(1);
        f.write('http://www.indeed.com'+thisURL+'\n')
        print "url number:"+str(urlnum)
        urllib.urlretrieve('http://www.indeed.com'+thisURL,"resumes/"+re.sub(r'\W+', '-',url1.group(2).replace(" ", "_"))+".html")#retrieving html of each individual resume.
        time.sleep(1)
        print thisURL
f.close()