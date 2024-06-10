import * as React from 'react';
import { Card, CardContent, Container, Grid, Typography } from "@mui/material";
import Copyright from "@/components/Copyright";

export const metadata = {
  title: "NLP Platform"
}

export default function Home() {
  return (
    <Container maxWidth="lg" sx={{ mt: 4, mb: 4 }}>
      <Typography variant="h4" sx={{ pb: 4 }}>
        Welcome to NLP Platform!
      </Typography>
      <Grid container spacing={3}>
        <Grid item xs={12} md={6}>
          <Card sx={{ minHeight: 175 }}>
            <CardContent>
              <Typography variant="h5">Unlock the Secrets of Text Data</Typography>
              <Typography variant="body1">
                Our powerful NLP platform empowers you to transform raw text into actionable insights.
                Unearth hidden trends, understand customer sentiment, and gain a deeper understanding of your audience.
              </Typography>
            </CardContent>
          </Card>
        </Grid>
        <Grid item xs={12} md={6}>
          <Card sx={{ minHeight: 175 }}>
            <CardContent>
              <Typography variant="h5">Turn Reviews into Gold</Typography>
              <Typography variant="body1">
                Stop guessing what your customers think! Analyze their reviews with our sentiment analysis tool.
                Identify areas for improvement, gauge satisfaction, and track the impact of changes you make.
              </Typography>
            </CardContent>
          </Card>
        </Grid>
        <Grid item xs={12} md={6}>
          <Card sx={{ minHeight: 175 }}>
            <CardContent>
              <Typography variant="h5">Speak the World&apos;s Languages</Typography>
              <Typography variant="body1">
                Break down language barriers and reach a global audience with our seamless machine translation.
                Translate documents, websites, or any text with exceptional accuracy, adapting to different contexts for natural-sounding results.
              </Typography>
            </CardContent>
          </Card>
        </Grid>
        <Grid item xs={12} md={6}>
          <Card sx={{ minHeight: 175 }}>
            <CardContent>
              <Typography variant="h5">Get Started Today!</Typography>
              <Typography variant="body1">
                Experience the power of NLP firsthand!  Jump over to the next page to try out our sentiment analysis or machine translation tool and see how it can transform your text data.
              </Typography>
            </CardContent>
          </Card>
        </Grid>
      </Grid>
      <Copyright sx={{ pt: 4 }} />
    </Container>
  );
}
