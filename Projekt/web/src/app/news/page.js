import * as React from 'react';
import Copyright from "@/components/Copyright";
import NextLink from 'next/link';
import { Box, Button, Card, CardContent, Container, Grid, Typography } from "@mui/material";

export const metadata = {
  title: "News - NLP Platform"
}

export default function News() {
  return (
    <Container maxWidth="sm" sx={{ mt: 4, mb: 4 }}>
      <Box
        sx={{
          marginTop: 8,
          display: 'flex',
          flexDirection: 'column',
          alignItems: 'center',
          gap: 4
        }}
      >
        <Grid item xs={8}>
          <Card>
            <CardContent>
              <Typography variant="h5">Lorem ipsum</Typography>
              <Typography variant="body1">
                Lorem ipsum dolor sit amet, consectetur adipiscing elit. In ac purus dolor. Proin sapien odio, rutrum sit amet lectus sit amet, viverra tempor erat. Donec non quam a lacus tincidunt vehicula. Curabitur varius nibh convallis imperdiet sollicitudin. Suspendisse tristique eros a erat lacinia, nec finibus risus elementum. Morbi volutpat dui vitae tortor auctor, vel rhoncus nisl consectetur. Cras ultricies vehicula efficitur. Fusce sodales iaculis quam ac volutpat. Nam sem elit, gravida id dui at, accumsan convallis risus. Phasellus posuere aliquam sagittis.
              </Typography>
            </CardContent>
          </Card>
        </Grid>
        <Grid item xs={8}>
          <Card>
            <CardContent>
              <Typography variant="h5">Lorem ipsum</Typography>
              <Typography variant="body1">
                Lorem ipsum dolor sit amet, consectetur adipiscing elit. In ac purus dolor. Proin sapien odio, rutrum sit amet lectus sit amet, viverra tempor erat. Donec non quam a lacus tincidunt vehicula. Curabitur varius nibh convallis imperdiet sollicitudin. Suspendisse tristique eros a erat lacinia, nec finibus risus elementum. Morbi volutpat dui vitae tortor auctor, vel rhoncus nisl consectetur. Cras ultricies vehicula efficitur. Fusce sodales iaculis quam ac volutpat. Nam sem elit, gravida id dui at, accumsan convallis risus. Phasellus posuere aliquam sagittis.
              </Typography>
            </CardContent>
          </Card>
        </Grid>
        <Grid item xs={8}>
          <Card>
            <CardContent>
              <Typography variant="h5">Lorem ipsum</Typography>
              <Typography variant="body1">
                Lorem ipsum dolor sit amet, consectetur adipiscing elit. In ac purus dolor. Proin sapien odio, rutrum sit amet lectus sit amet, viverra tempor erat. Donec non quam a lacus tincidunt vehicula. Curabitur varius nibh convallis imperdiet sollicitudin. Suspendisse tristique eros a erat lacinia, nec finibus risus elementum. Morbi volutpat dui vitae tortor auctor, vel rhoncus nisl consectetur. Cras ultricies vehicula efficitur. Fusce sodales iaculis quam ac volutpat. Nam sem elit, gravida id dui at, accumsan convallis risus. Phasellus posuere aliquam sagittis.
              </Typography>
            </CardContent>
          </Card>
        </Grid>
      </Box>
      <Copyright sx={{ pt: 4 }} />
    </Container>
  );
}