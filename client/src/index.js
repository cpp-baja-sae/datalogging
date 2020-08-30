import { createBrowserHistory } from 'history';
import React from 'react';
import ReactDOM from 'react-dom';

import './index.css';
import App from './App';

let root_template = (<App />);

ReactDOM.render(root_template, document.getElementById('root'));
