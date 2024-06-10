import * as React from 'react';
import { AppRouterCacheProvider } from '@mui/material-nextjs/v14-appRouter';
import Wrapper from '@/components/Wrapper';

export const metadata = {
  title: "NLP Platform",
  description: "Welcome NLP Platform! Currently available features are Machine Translation and Sentiment Analysis.",
};

export default function RootLayout({ children }) {
  return (
    <html lang="en">
      <body>
        <AppRouterCacheProvider options={{ enableCssLayer: true }}>
          <Wrapper>
            {children}
          </Wrapper>
        </AppRouterCacheProvider>
      </body>
    </html>
  );
}
