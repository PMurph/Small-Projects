set CLASSPATH=.;bin\;libraries\gluegen-rt.jar;libraries\jogl-all.jar

erase bin\*.class

javac -d bin\ -cp %classpath% src\*.java
java -cp %classpath% Main 