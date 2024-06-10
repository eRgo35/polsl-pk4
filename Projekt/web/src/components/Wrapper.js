'use client'
import * as React from 'react';
import { Box, Container, CssBaseline, Divider, Grid, IconButton, List, Paper, Toolbar, Typography, darken, useMediaQuery } from "@mui/material";
import Copyright from "@/components/Copyright";
import { ThemeProvider } from "@mui/material/styles";
import { lightTheme, darkTheme } from '@/theme';
import MenuIcon from '@mui/icons-material/Menu';
import ChevronLeftIcon from '@mui/icons-material/ChevronLeft';
import GitHubIcon from '@mui/icons-material/GitHub';
import { AppBar } from '@/components/AppBar';
import { Drawer } from '@/components/Drawer';
import Brightness4Icon from '@mui/icons-material/Brightness4';
import Brightness7Icon from '@mui/icons-material/Brightness7';
import { getCookie, setCookie } from 'cookies-next'
import { HomeListItem, MainListItem, SecondaryListItem } from '@/components/ListItems';
import { usePathname } from 'next/navigation';

export default function Wrapper({ children }) {
  const [darkMode, setDarkMode] = React.useState(true);
  
  const theme = darkMode ? darkTheme : lightTheme;

  const isLargerThanSm = useMediaQuery(theme.breakpoints.up('md')); 
  const [open, setOpen] = React.useState(isLargerThanSm);
  const [pageTitle, setPageTitle] = React.useState("NLP Platform");
  
  const pathname = usePathname();

  React.useEffect(() => {
    const paths = {
      '': 'NLP Platform',
      'news': 'News',
      'api': 'API',
      'translate': 'Machine Translation',
      'sentiment': 'Sentiment Analysis',
      'detect': 'Language Detection',
      'anonymize': 'Anonymization',
      'signin': 'Sign in',
      'signup': 'Sign up',
      'preferences': 'Preferences',
      'developer': 'Developer Mode'
    }  

    setPageTitle(paths[pathname.substring(1)])
  }, [pathname])

  React.useEffect(() => {
    setOpen(isLargerThanSm);
  }, [isLargerThanSm]);

  const toggleDrawer = () => {
    setOpen(!open)
  };

  const closeDrawer = () => {
    setOpen(false);
  }

  React.useEffect(() => {
    const stored = getCookie('dark');
    // let color = (stored === 'true') ? true : (stored === 'false') ? false : true
    setDarkMode(stored !== 'false');
  }, []);

  const toggleColorMode = () => {
    setCookie('dark', !darkMode);
    setDarkMode(!darkMode);
  };


  return (
    <ThemeProvider theme={theme}>
      <CssBaseline />
      <Box sx={{ display: 'flex' }}>
        <AppBar position="absolute" open={open}>
          <Toolbar
            sx={{
              pr: '24px', // keep right padding when drawer closed
            }}
          >
            <IconButton
              edge="start"
              color="inherit"
              aria-label="open drawer"
              onClick={toggleDrawer}
              sx={{
                marginRight: '36px',
                ...(open && { display: 'none' }),
              }}
            >
              <MenuIcon />
            </IconButton>
            <Typography
              component="h1"
              variant="h6"
              color="inherit"
              noWrap
              sx={{ flexGrow: 1 }}
            >
              {pageTitle}
            </Typography>
            <IconButton sx={{ ml: 1 }} onClick={toggleColorMode} color="inherit">
              {theme.palette.mode === 'dark' ? <Brightness7Icon /> : <Brightness4Icon />}
            </IconButton>
            {/* <IconButton color="inherit" href="https://github.com/eRgo35/nlp-platform">
              <GitHubIcon />
            </IconButton> */}
          </Toolbar>
        </AppBar>
        <Drawer variant="permanent" open={open}>
          <Toolbar
            sx={{
              display: 'flex',
              alignItems: 'center',
              justifyContent: 'flex-end',
              px: [1],
            }}
          >
            <IconButton onClick={toggleDrawer}>
              <ChevronLeftIcon />
            </IconButton>
          </Toolbar>
          <Divider />
          <List component="nav">
            <HomeListItem drawerAction={closeDrawer} size={isLargerThanSm} />
            <Divider sx={{ my: 1 }} />
            <MainListItem drawerAction={closeDrawer} size={isLargerThanSm} />
            <Divider sx={{ my: 1 }} />
            <SecondaryListItem drawerAction={closeDrawer} size={isLargerThanSm} />
          </List>
        </Drawer>
        <Box
          component="main"
          sx={{
            backgroundColor: (theme) =>
              theme.palette.mode === 'light'
                ? theme.palette.grey[100]
                : theme.palette.grey[900],
            flexGrow: 1,
            height: '100vh',
            overflow: 'auto',
          }}
        >
          <Toolbar />
          {children}
        </Box>
      </Box>
    </ThemeProvider>
  );
}
