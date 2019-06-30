import React, { Component } from 'react';

import { MOTOR_SETTINGS_ENDPOINT }  from  '../constants/Endpoints';
import { restComponent } from '../components/RestComponent';
import SectionContent from '../components/SectionContent';
// import MotorSettingsForm from '../forms/MotorSettingsForm';

class MotorSettings extends Component {


    render() {
        return (
            <SectionContent title="Motor Settings">

            </SectionContent>
        )
    }

}

export default restComponent(MOTOR_SETTINGS_ENDPOINT, MotorSettings);
