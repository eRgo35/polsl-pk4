import styles from "../page.module.css"

export default function Header({ title = "Welcome", path = "" }) {
  return (
  <nav className="navbar navbar-expand-lg"> 
    <div className="container-fluid">
      <a className="navbar-brand" href={"/" + path}>
        {title}
      </a>
    <button className="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbar-collapse-1" aria-controls="navbar-collapse-1" aria-expanded="false" aria-label="Toggle navigation">
      <span className="navbar-toggler-icon"></span>
    </button>
  </div>
</nav>
  );
}
