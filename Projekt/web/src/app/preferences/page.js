import * as React from 'react';
import Copyright from "@/components/Copyright";
import NextLink from 'next/link';
import { Grid, Container, Paper, Typography } from "@mui/material";

export const metadata = {
  title: "Preferences - NLP Platform"
}

export default function Preferences() {
  return (
    <Container maxWidth="lg" sx={{ mt: 4, mb: 4 }}>
      <Grid container spacing={2} justifyContent="center">
        <Grid item xs={12} md={6}>
          <Paper sx={{ padding: 3 }}>
            <Typography variant="h5" sx={{ mb: 2 }}>
              Preferences
            </Typography>
            This page is currently work in progress.
          </Paper>
        </Grid>
      </Grid>
      <Copyright sx={{ pt: 4 }} />
    </Container>
  );
}