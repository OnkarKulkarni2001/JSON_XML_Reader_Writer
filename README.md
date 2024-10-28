# JSON_XML_Reader_Writer

Welcome to my another project where you can choose your own preferences, doesn't it sound interesting? If it doesn't let me explain what exactly it is!

## Description 📝

So in this project you can choose your own language preference and whatever language you choose, all the commands will automatically translate to your preferred language. This is done with the help of JSON/XML configuration reader writer. Where there are files in .json and .xml format which will be read by respective configuration reader writer classes and as per your preferences the preferences.json or preferences.xml file will be written, again this happens totally at backend, user only needs to choose preference!

Next time when the program is ran, it will automatically fetch the preferences.json or preferences.xml file from the user and load the user preferences!

## Libraries Used 📚

1) pugixml

2) rapidxml

3) nlohmann

## Current Settings ⚙️

Currently it is hardcoded to read only json config files but if you want to use xml config files you dont have to change a lot of things! I have taken care of everything! Just open the cTranslator.cpp and make line 11 a comment and uncomment the line 12. Isn't that simple?

## Build Instructions

1) Run the solution

2) Link the libraries in project properties if not linked already (You probably don't need to do this step as it will be automatically set for you!)

3) Right click on the project in solution explored and click on build solution

4) Voila! it's built!

## Thank you for using my application!😊