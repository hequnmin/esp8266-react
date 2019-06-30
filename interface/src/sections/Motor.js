import React, { Component } from 'react';
import { Redirect, Switch } from 'react-router-dom';

import Tabs from '@material-ui/core/Tabs';
import Tab from '@material-ui/core/Tab';

import AuthenticatedRoute from '../authentication/AuthenticatedRoute';
import MenuAppBar from '../components/MenuAppBar';
import MotorSettings from '../containers/MotorSettings';
import MotorStatus from '../containers/MotorStatus';
import { withAuthenticationContext } from '../authentication/Context.js';

class Motor extends Component {
    
    render() {
        const { authenticationContext } = this.props;
        return (
            <MenuAppBar sectionTitle="Motor">
                 <Tabs value={this.props.match.url} onChange={this.handleTabChange} indicatorColor="primary" textColor="primary" variant="fullWidth">
                    <Tab value="/motor/status" label="Motor Status" />
                    <Tab value="/motor/settings" label="Motor Settings" disabled={!authenticationContext.isAdmin()} />
                </Tabs>
                <Switch>
                    <AuthenticatedRoute exact={true} path="/motor/status" component={MotorStatus} />
                    <AuthenticatedRoute exact={true} path="/motor/settings" component={MotorSettings} />
                    <Redirect to="/motor/status" />
                </Switch>
            </MenuAppBar>
        )
    }
}

export default withAuthenticationContext(Motor);