import styles from "../page.module.css";

import Header from "../components/Header";
import SideBar from "../components/SideBar";
import Preferences from "../components/Preferences";
import Footer from "../components/Footer";

export default function Home() {
  return (
    <main className={styles.main}>
      <Header />
      <SideBar />
      <Preferences />
      {/* <Footer /> */}
    </main>
  );
}


