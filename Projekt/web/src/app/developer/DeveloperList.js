"use client"
import * as React from 'react';
import { Badge, IconButton, LinearProgress, List, ListItem, ListItemIcon, ListItemSecondaryAction, ListItemText, ListSubheader } from "@mui/material";
import { Refresh } from '@mui/icons-material';
import PublicIcon from '@mui/icons-material/Public';
import PublicOffIcon from '@mui/icons-material/PublicOff';
import { baseUrl } from '../lib/backend';

export default function DeveloperList() {
  const [status, setStatus] = React.useState("Refreshing...");
  const [isLoading, setIsLoading] = React.useState(true);
  const [isOnline, setIsOnline] = React.useState(false);

  const pingConnection = () => {
    setIsLoading(true);
    setStatus("Refreshing...");
    setIsOnline(false);

    setTimeout(async () => {
      try {
        await fetch(`${baseUrl}/api/ping`)
          .then((res) => res.json())
          .then((data) => {
            setStatus(data.data);
            setIsOnline(true);
          })
      }
      catch (err) {
        console.error(err);
        setStatus("Offline");
        setIsOnline(false);
      }

      setIsLoading(false);
    }, 150);
  }

  React.useEffect(() => {
    pingConnection();
  }, [])

  return (
    <List
      subheader={
        <ListSubheader>
          API Status
        </ListSubheader>
      }
    >
      <ListItem>
        <ListItemIcon>
          <Badge color={isOnline ? "success" : "error"} variant="dot">
            {isOnline ? <PublicIcon /> : <PublicOffIcon />}
          </Badge>
        </ListItemIcon>
        <ListItemText primary={status} />
        <ListItemSecondaryAction>
          <IconButton onClick={pingConnection}>
            <Refresh />
          </IconButton>
        </ListItemSecondaryAction>
      </ListItem>
      {isLoading ? <LinearProgress /> : ""}
    </List>
  );
}