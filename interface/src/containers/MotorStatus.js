import React, { Component } from 'react';

import SectionContent from '../components/SectionContent';
import { MOTOR_STATUS_ENDPOINT } from '../constants/Endpoints';
import { restComponent } from '../components/RestComponent';

class MotorStatus extends Component {
    render() {
        return (
            <SectionContent title="Motor Status">

            </SectionContent>
        )
    }
}

export default restComponent(MOTOR_STATUS_ENDPOINT, MotorStatus);

