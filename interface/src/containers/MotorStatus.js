import React, { Component, Fragment } from 'react';

import { withStyles } from '@material-ui/core/styles';
import Button from '@material-ui/core/Button';
import LinearProgress from '@material-ui/core/LinearProgress';
import Typography from '@material-ui/core/Typography';
import List from '@material-ui/core/List';
import ListItem from '@material-ui/core/ListItem';
import ListItemText from '@material-ui/core/ListItemText';
import ListItemAvatar from '@material-ui/core/ListItemAvatar';
import Avatar from '@material-ui/core/Avatar';
import Divider from '@material-ui/core/Divider';

import SettingsInputAntennaIcon from '@material-ui/icons/SettingsInputAntenna';

import GraphicEqIcon from '@material-ui/icons/GraphicEq';
import RotateRightIcon from '@material-ui/icons/RotateRight';
import RotateLeftIcon from '@material-ui/icons/RotateLeft';
import SettingsInputComponentIcon from '@material-ui/icons/SettingsInputComponent';

import { restComponent } from '../components/RestComponent';
import SectionContent from '../components/SectionContent';

import * as Highlight from '../constants/Highlight';
import { MOTOR_STATUS_ENDPOINT } from '../constants/Endpoints';

const styles = theme => ({
  ["motorStatus_" + Highlight.SUCCESS]: {
    backgroundColor: theme.palette.highlight_success
  },
  ["motorStatus_" + Highlight.IDLE]: {
    backgroundColor: theme.palette.highlight_idle
  },
  fetching: {
    margin: theme.spacing(4),
    textAlign: "center"
  },
  button: {
    marginRight: theme.spacing(2),
    marginTop: theme.spacing(2),
  }
});

class MotorStatus extends Component {

	componentDidMount() {
    this.props.loadData();
	}

	motorStatusHighlight(data) {
    return data.active ? Highlight.SUCCESS : Highlight.IDLE;
	}

	motorStatus(data) {
    return data.active ? "Active" : "Inactive";
	}
	
	createListItems(data, classes) {
    return (
      <Fragment>
        <ListItem>
          <ListItemAvatar>
            <Avatar className={classes["motorStatus_" + this.motorStatusHighlight(data)]}>
              <SettingsInputAntennaIcon />
            </Avatar>
          </ListItemAvatar>
          <ListItemText primary="Status" secondary={this.motorStatus(data)} />
        </ListItem>
        <Divider variant="inset" component="li" />
        <ListItem>
          <ListItemAvatar>
            <Avatar>
							<GraphicEqIcon />
						</Avatar>
          </ListItemAvatar>
          <ListItemText primary="Freq MHz" secondary={data.motor_freq_val} />
        </ListItem>
        <Divider variant="inset" component="li" />
        <ListItem>
          <ListItemAvatar>
            <Avatar>
              <SettingsInputComponentIcon />
            </Avatar>
          </ListItemAvatar>
          <ListItemText primary="Freq Pin" secondary={data.motor_freq_pin} />
        </ListItem>
        <Divider variant="inset" component="li" />
        <ListItem>
          <ListItemAvatar>
            <Avatar>
							{
								data.motor_dirc ? <RotateRightIcon /> : <RotateLeftIcon />
							}
            </Avatar>
          </ListItemAvatar>
          <ListItemText primary="Direct (Anti)clockwise" secondary={data.motor_dirc ? "Clockwise" : "Anticlockwise"} />
        </ListItem>
				<Divider variant="inset" component="li" />
        <ListItem>
          <ListItemAvatar>
            <Avatar>
              <SettingsInputComponentIcon />
            </Avatar>
          </ListItemAvatar>
          <ListItemText primary="Direct Pin" secondary={data.motor_direct_pin} />
        </ListItem>
        <Divider variant="inset" component="li" />
      </Fragment>
    );
	}
	
	renderMotorStatus(data, classes) {
    return (
      <div>
        <List>
          <Fragment>
            {this.createListItems(data, classes)}
          </Fragment>
        </List>
        <Button variant="contained" color="secondary" className={classes.button} onClick={this.props.loadData}>
          Refresh
        </Button>
      </div>
    );
  }

	render() {
			const { data, fetched, errorMessage, classes } = this.props;

			return (
					<SectionContent title="Motor Status">
						{
							!fetched ?
							<div>
								<LinearProgress className={classes.fetching} />
								<Typography variant="h4" className={classes.fetching}>
									Loading...
								</Typography>
							</div>
							:
							data ? this.renderMotorStatus(data, classes)
								:
								<div>
									<Typography variant="h4" className={classes.fetching}>
										{errorMessage}
									</Typography>
									<Button variant="contained" color="secondary" className={classes.button} onClick={this.props.loadData}>
										Refresh
									</Button>
								</div>
						}
					</SectionContent>
			)
	}
}

export default restComponent(MOTOR_STATUS_ENDPOINT, withStyles(styles)(MotorStatus));

