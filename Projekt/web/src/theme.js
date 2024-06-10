'use client';
import { Roboto } from 'next/font/google';
import { createTheme, alpha, getOverlayAlpha } from '@mui/material/styles';

const roboto = Roboto({
  weight: ['300', '400', '500', '700'],
  subsets: ['latin'],
  display: 'swap',
});

function overridesForList() {
  const elevations = new Array(24).fill(null).map((_, i) => i + 1);
  return elevations.reduce((acc, curr) => {
    const calculatedColor = alpha('#fff', parseFloat(getOverlayAlpha(curr)));
    return {
      ...acc,
      [`&.MuiPaper-elevation${curr} .MuiListSubheader-sticky`]: {
        backgroundImage: `linear-gradient(${calculatedColor}, ${calculatedColor})`,
      },
    };
  }, {});
}

const lightTheme = createTheme({
  palette: {
    mode: 'light',
  },
  typography: {
    fontFamily: roboto.style.fontFamily,
  },
  // components: {
  //   MuiAlert: {
  //     styleOverrides: {
  //       root: ({ ownerState }) => ({
  //         ...(ownerState.severity === 'info' && {
  //           backgroundColor: '#60a5fa',
  //         }),
  //       }),
  //     },
  //   },
  // },
});

const darkTheme = createTheme({
  palette: {
    mode: 'dark',
  },
  typography: {
    fontFamily: roboto.style.fontFamily,
  },
  components: {
    MuiPaper: {
      styleOverrides: {
        root: {
          ...overridesForList(),
        },
      },
    },
  },
});

export { lightTheme, darkTheme };