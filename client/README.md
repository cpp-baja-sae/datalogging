# Client

This component runs on the web browser of any computer connected to the server
component. It is responsible for providing a nice interface to both realtime
and historic data, allowing for various forms of analysis.

## Development notes.
This component uses NodeJS. You may need to install it with 
`sudo apt install nodejs`. Once that is installed, you may need to run
`npm i` inside this folder to install the packages this project uses. 

Once these steps are complete, `run.sh` will start a development server on port 
3000. When this server is active, any changes to the source code will 
automatically trigger a recompile of everything which, once complete, will
trigger all connected browsers to reload the page. You may need to stop and 
restart the dev server after adding or deleting files, and it can also help get 
rid of any particularly weird or sudden bugs. 

`build.sh` will create a publishable version of the website in the build/ 
folder. The server component is configured to serve the webpage from this folder 
when it is started up, so you do not have to move the files after they finish 
building. public/ contains files that will be directly copied to the website. 
src/ contains files that will be squished down and compiled with any required 
libraries into a single javascript file, which is then included with the rest of 
the website.

Source code has the extension `.tsx`, because it is written in TypeScript (a 
version of JavaScript with type checking) and supports JSX (a way to write
HTML inside of JavaScript code.) You can read more about it at these links:
https://medium.com/swlh/convert-your-javascript-react-app-to-typescript-the-easy-guide-631592dc1876
https://www.typescriptlang.org/docs/handbook/jsx.html
