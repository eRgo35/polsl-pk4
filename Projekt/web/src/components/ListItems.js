import * as React from 'react';
import ListItemButton from '@mui/material/ListItemButton';
import ListItemIcon from '@mui/material/ListItemIcon';
import ListItemText from '@mui/material/ListItemText';
import ListSubheader from '@mui/material/ListSubheader';
import LoginIcon from '@mui/icons-material/Login';
import TranslateIcon from '@mui/icons-material/Translate';
import LanguageIcon from '@mui/icons-material/Language';
import SentimentSatisfiedAltIcon from '@mui/icons-material/SentimentSatisfiedAlt';
import FingerprintIcon from '@mui/icons-material/Fingerprint';
import CodeIcon from '@mui/icons-material/Code';
import HomeIcon from '@mui/icons-material/Home';
import FeedIcon from '@mui/icons-material/Feed';
import SettingsIcon from '@mui/icons-material/Settings';
import ApiIcon from '@mui/icons-material/Api';
import Link from 'next/link';
import { usePathname } from 'next/navigation'

export const HomeListItem = ({ drawerAction, size }) => {
  const pathname = usePathname()

  return (
    <React.Fragment>
      <ListItemButton selected={pathname === "/"} href="/" component={Link} onClick={!size && drawerAction}>
        <ListItemIcon>
          <HomeIcon />
        </ListItemIcon>
        <ListItemText primary="Home" />
      </ListItemButton>
      <ListItemButton selected={pathname === "/news"} href="/news" component={Link} onClick={!size && drawerAction}>
        <ListItemIcon>
          <FeedIcon />
        </ListItemIcon>
        <ListItemText primary="News" />
      </ListItemButton>
      <ListItemButton selected={pathname === "/api"} href="/api" component={Link} onClick={!size && drawerAction}>
        <ListItemIcon>
          <ApiIcon />
        </ListItemIcon>
        <ListItemText primary="API" />
      </ListItemButton>
    </React.Fragment>
  );
};

export const MainListItem = ({ drawerAction, size }) => {
  const pathname = usePathname()

  return (
    <React.Fragment>
      <ListSubheader component="div" inset>
        Language Processing
      </ListSubheader>
      <ListItemButton selected={pathname === "/translate"} href="/translate" component={Link} onClick={!size && drawerAction}>
        <ListItemIcon>
          <TranslateIcon />
        </ListItemIcon>
        <ListItemText primary="Machine Translation" />
      </ListItemButton>
      <ListItemButton selected={pathname === "/sentiment"} href="/sentiment" component={Link} onClick={!size && drawerAction}>
        <ListItemIcon>
          <SentimentSatisfiedAltIcon />
        </ListItemIcon>
        <ListItemText primary="Sentiment Analysis" />
      </ListItemButton>
      <ListItemButton selected={pathname === "/detect"} href="/detect" component={Link} onClick={!size && drawerAction}>
        <ListItemIcon>
          <LanguageIcon />
        </ListItemIcon>
        <ListItemText primary="Language Detection" />
      </ListItemButton>
      <ListItemButton selected={pathname === "/anonymize"} href="/anonymize" component={Link} onClick={!size && drawerAction}>
        <ListItemIcon>
          <FingerprintIcon />
        </ListItemIcon>
        <ListItemText primary="Anonymization" />
      </ListItemButton>
    </React.Fragment>
  );
};

export const SecondaryListItem = ({ drawerAction, size }) => {
  const pathname = usePathname()

  return (
    <React.Fragment>
      <ListSubheader component="div" inset>
        More
      </ListSubheader>
      <ListItemButton selected={pathname === "/signin"} href="/signin" component={Link} onClick={!size && drawerAction}>
        <ListItemIcon>
          <LoginIcon />
        </ListItemIcon>
        <ListItemText primary="Sign in" />
      </ListItemButton>
      <ListItemButton selected={pathname === "/preferences"} href="/preferences" component={Link} onClick={!size && drawerAction}>
        <ListItemIcon>
          <SettingsIcon />
        </ListItemIcon>
        <ListItemText primary="Preferences" />
      </ListItemButton>
      <ListItemButton selected={pathname === "/developer"} href="/developer" component={Link} onClick={!size && drawerAction}>
        <ListItemIcon>
          <CodeIcon />
        </ListItemIcon>
        <ListItemText primary="Developer Mode" />
      </ListItemButton>
    </React.Fragment>
  );
};
