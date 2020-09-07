# Client

This component runs on the web browser of any computer connected to the server
component. It is responsible for providing a nice interface to both realtime
and historic data, allowing for various forms of analysis.

## Development notes.
This component uses NodeJS. You may need to install it with 
`sudo apt install nodejs`. Once that is installed, you may need to run
`npm i` inside this folder to install the packages this project uses. Once
these steps are complete, `run.sh` will start a development server on port 3000.
When this server is active, any changes to the source code will automatically
cause any connected browsers to refresh their page, thereby displaying the
changes. You may need to stop and restart the dev server after adding or 
deleting files, and it can also help get rid of any particularly weird or sudden
bugs. `build.sh` will create a publishable version of the website in the
build/ folder. The server component is configured to serve the webpage from
this folder when it is started up, so you do not have to move the files after
they finish building. public/ contains files that will be directly copied to the 
website. src/ contains files that will be squished down and compiled with any 
required libraries into a single javascript file, which is then included with 
the rest of the website.
